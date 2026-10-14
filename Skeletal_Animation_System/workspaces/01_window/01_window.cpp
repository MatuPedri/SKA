#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SKA/Window.hpp>

int main()
{
	ska::Window window(800, 600);
	while(!window.isClosed())
	{
		window.pollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);	
		window.swap();

		if (glfwGetKey(window.handle(), GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window.handle(), GLFW_TRUE);
		}
	}
	return 0;
}