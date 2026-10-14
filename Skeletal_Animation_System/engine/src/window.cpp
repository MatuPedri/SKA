#include "../include/SKA/Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

ska::Window::Window(const u16 w, const u16 h)
{
	if (!glfwInit())
	{
		std::fprintf(stderr, "[Window] glfwInit failed\n");
		std::abort();
	}

	width_ = w;
	height_ = h;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	glfw_window_ = glfwCreateWindow(width_, height_, "SKA Engine", nullptr, nullptr);

	if (!glfw_window_)
	{
		std::fprintf(stderr, "[Window] glfwCreateWindow failed (does your GPU support OpenGL 4.5?)\n");
		glfwTerminate();
		std::abort();
	}

	glfwMakeContextCurrent(glfw_window_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::fprintf(stderr, "[Window] glad could not load OpenGL\n");
		glfwDestroyWindow(glfw_window_);
		glfwTerminate();
		std::abort();
	}
}

ska::Window::~Window()
{
	glfwDestroyWindow(glfw_window_);
	glfwTerminate();
}

bool ska::Window::isClosed() const
{
	return glfwWindowShouldClose(glfw_window_) == GLFW_TRUE;
}

void ska::Window::swap()
{
	glfwSwapBuffers(glfw_window_);
}

void ska::Window::pollEvents()
{
	int w, h;
	glfwGetWindowSize(glfw_window_, &w, &h);

	width_ = static_cast<u16>(w);
	height_ = static_cast<u16>(h);

	glfwPollEvents();
}

GLFWwindow* ska::Window::handle() const
{
		return glfw_window_;
}