#include "core.h"
#include "Window.h"
#include "Input.h"

using namespace MinecraftClone;

constexpr int width = 1920;
constexpr int height = 1080;
const char* title = "Minecraft Clone";

int exitWithError(const char* msg)
{
	std::cout << msg;
	glfwTerminate();
	return -1;
}

int main()
{
	glfwInit();

	Window window(width, height, title);
	if (window.nativeWindow == nullptr)
	{
		return exitWithError("Failed to create GLFW window.\n");
	}
	window.setCallbacks();

	if (!gladLoadGL())
	{
		return exitWithError("Failed to initialize GLAD.\n");
	}
	
	glViewport(0, 0, window.windowWidth, window.windowHeight);
	while (!glfwWindowShouldClose(window.nativeWindow))
	{
		// Clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (Input::isKeyDown(GLFW_KEY_E))
			std::cout << "E\n.";

		glfwSwapBuffers(window.nativeWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}