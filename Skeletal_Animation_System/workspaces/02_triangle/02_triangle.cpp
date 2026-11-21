#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SKA/Window.hpp>
#include <SKA/renderer/shader.hpp>
#include <SKA/renderer/vertex.hpp>
#include <SKA/renderer/mesh.hpp>
#include <SKA/renderer/shader_program.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct GlobalState {
		double dt;
		double lastFrame;
		double currentFrame;
		double FPS;
		double msPerFrame;
}global;

void imGuiInit(ska::Window& window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.handle(), true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void imGuiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void imGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imGuiShutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void imGuiDraw()
{
	ImGui::SetNextWindowPos(ImVec2(300, 100), ImGuiCond_FirstUseEver);
	ImGui::Begin("FPS");
	static double smoothFPS = 0.0;
	smoothFPS = 0.9 * smoothFPS + 0.1 * global.FPS;
	static double smoothMsPerFrame = 0.0;
	smoothMsPerFrame = 0.9 * smoothMsPerFrame + 0.1 * global.msPerFrame;
	ImGui::Text("FPS: %.2f", smoothFPS);
	ImGui::Text("Frame time: %.3f ms", smoothMsPerFrame);
	ImGui::End();
}

bool imGuiDrawTriangleInfo(std::vector<ska::Vertex>& vertices, const std::vector<u32>& indices)
{
	bool changed = false;
	ImGui::SetNextWindowPos(ImVec2(300, 200), ImGuiCond_FirstUseEver);
	ImGui::Begin("Triangle Info");
	ImGui::Text("Vertices: %d", static_cast<int>(vertices.size()));
	ImGui::Text("Indices: %d", static_cast<int>(indices.size()));
	changed = ImGui::DragFloat3("Vertex 0 Position", &vertices[0].position[0], 0.01f) || changed;
	changed = ImGui::DragFloat3("Vertex 1 Position", &vertices[1].position[0], 0.01f) || changed;
	changed = ImGui::DragFloat3("Vertex 2 Position", &vertices[2].position[0], 0.01f) || changed;
	ImGui::End();

	return changed;
}

int main()
{
	ska::Window window(800, 600);
	glfwSwapInterval(0);
	ska::Shader vertex_shader;
	ska::Shader fragment_shader;
	ska::ShaderProgram shader_program;

	global.dt = 0.0;
	global.lastFrame = glfwGetTime();
	global.currentFrame = 0.0;
	global.FPS = 0.0;
	global.msPerFrame = 0.0;
	imGuiInit(window);

	vertex_shader.loadSourceFromFile(ska::Shader::Type::Vertex, "assets/shaders/basic.vs");
	fragment_shader.loadSourceFromFile(ska::Shader::Type::Fragment, "assets/shaders/basic.fs");
	fragment_shader.compile();
	vertex_shader.compile();

	shader_program.attachShader(&vertex_shader);
	shader_program.attachShader(&fragment_shader);
	shader_program.link();

	std::vector<ska::Vertex> vertices = {
		{ {-0.5f, -0.5f, 0.0f}, {0, 0, 1} },
		{ { 0.5f, -0.5f, 0.0f}, {0, 0, 1} },
		{ { 0.0f,  0.5f, 0.0f}, {0, 0, 1} }
	};

	std::vector<u32> indices = { 0, 1, 2 };
	ska::Mesh triangle_mesh(vertices, indices);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	while(!window.isClosed())
	{
		window.pollEvents();

		glViewport(0, 0, window.getWidth(), window.getHeight());
		projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		shader_program.use();
		shader_program.setMat4("view", view);
		shader_program.setMat4("projection", projection);
		shader_program.setMat4("model", model);
		triangle_mesh.draw();

		imGuiNewFrame();
		imGuiDraw();
		if(imGuiDrawTriangleInfo(vertices, indices))
		{
			triangle_mesh.updateVertices(vertices);
		}
		imGuiRender();


		window.swap();

		if (glfwGetKey(window.handle(), GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window.handle(), GLFW_TRUE);
		}

		global.currentFrame = glfwGetTime();
		global.dt = global.currentFrame - global.lastFrame;
		global.lastFrame = global.currentFrame;
		global.FPS = 1.0 / global.dt;
		global.msPerFrame = global.dt * 1000.0;
	}
	imGuiShutdown();
	return 0;
}