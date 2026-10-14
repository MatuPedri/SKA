#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SKA/Window.hpp>
#include <SKA/renderer/shader.hpp>
#include <SKA/renderer/shader_program.hpp>

int main()
{
	ska::Window window(800, 600);
	ska::Shader vertex_shader;
	ska::Shader fragment_shader;
	ska::ShaderProgram shader_program;

	vertex_shader.loadSourceFromFile(ska::Shader::Type::Vertex, "assets/shaders/basic.vs");
	fragment_shader.loadSourceFromFile(ska::Shader::Type::Fragment, "assets/shaders/basic.fs");
	fragment_shader.compile();
	vertex_shader.compile();

	shader_program.attachShader(&vertex_shader);
	shader_program.attachShader(&fragment_shader);
	shader_program.link();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
	};

	u32 VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while(!window.isClosed())
	{
		window.pollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);	
		shader_program.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.swap();

		if (glfwGetKey(window.handle(), GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window.handle(), GLFW_TRUE);
		}
	}
	return 0;
}