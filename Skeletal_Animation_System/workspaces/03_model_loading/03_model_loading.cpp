#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SKA/Window.hpp>
#include <SKA/renderer/shader.hpp>
#include <SKA/renderer/vertex.hpp>
#include <SKA/renderer/mesh.hpp>
#include <SKA/loaders/model_loader.hpp>
#include <SKA/renderer/shader_program.hpp>
#include <SKA/loaders/model_loader.hpp>
#include <SKA/animation/skinning.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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

	ska::Model modelGLB;
	modelGLB.loadModel("assets/models/CesiumMan.glb");

	ska::Mesh& mesh = *modelGLB.getMeshes()[0];
	const std::vector<ska::Vertex> vertices = mesh.getVertices();

	ska::CpuSkinner cpuSkinner(mesh);

	const ska::Skeleton& skeleton = modelGLB.getSkeleton();
	const auto globals = skeleton.computeGlobals(skeleton.bindLocals());
	const auto skinMatrices = skeleton.computeSkinMatrices(globals);

	cpuSkinner.skin(skinMatrices, mesh);

	const std::vector<ska::Vertex>& skinnedVertices = mesh.getVertices();
	float maxError = 0.0f;
	for (size_t i = 0; i < vertices.size(); ++i) {
		maxError = std::max(maxError, glm::length(skinnedVertices[i].position - vertices[i].position));
	}
	printf("Max diferencia de posicion en reposo: %g\n", maxError);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f));
	glEnable(GL_DEPTH_TEST);
	while(!window.isClosed())
	{
		window.pollEvents();

		glViewport(0, 0, window.getWidth(), window.getHeight());
		projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader_program.use();
		shader_program.setMat4("view", view);
		shader_program.setMat4("projection", projection);
		shader_program.setMat4("model", model);
		modelGLB.draw();

		imGuiNewFrame();
		imGuiDraw();
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