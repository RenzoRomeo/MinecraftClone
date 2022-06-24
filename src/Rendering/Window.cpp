#include "Window.h"
#include "../Input.h"

static void GLAPIENTRY ErrorCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

namespace MinecraftClone
{
	Window::Window(int width, int height, const char* title, bool fullscreen)
		: window_width(width), window_height(height)
	{
		glfwInit();

		// GLFW window hints
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWmonitor* primaryMonitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
		native_window = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);
		if (native_window == nullptr)
		{
			std::cout << "Failed to create GLFW window.\n";
			glfwTerminate();
		}
		glfwMakeContextCurrent(native_window);

		glfwSetInputMode(native_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGL())
			std::cout << "Failed to load GLAD.\n";

		glViewport(0, 0, window_width, window_height);

		SetCallbacks();

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(ErrorCallback, 0);
	}

	Window::~Window()
	{
		if (native_window)
			glfwDestroyWindow(native_window);
		glfwTerminate();
	}

	void Window::SetCallbacks()
	{
		if (native_window != nullptr)
		{
			glfwSetKeyCallback(native_window, Input::KeyCallback);
			glfwSetMouseButtonCallback(native_window, Input::MouseButtonCallback);
			glfwSetCursorPosCallback(native_window, Input::MouseCallback);
		}
	}

	void Window::Close()
	{
		if (native_window != nullptr)
			glfwSetWindowShouldClose(native_window, GLFW_TRUE);
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(native_window);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(native_window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::Clear(float r, float g, float b, float a)
	{
		glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
