#include "core.h"
#include "Window.h"
#include "Input.h"

#include "Cubes.h"

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

void GLAPIENTRY errorMessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if (type == GL_DEBUG_TYPE_ERROR)
	{
		std::cout << message << '\n';
	}
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

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(errorMessageCallback, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSetInputMode(window.nativeWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float dt = 0.016f;
	float frameStart = 0.0f;

	Cubes::init(window);
	
	glViewport(0, 0, window.windowWidth, window.windowHeight);
	while (!glfwWindowShouldClose(window.nativeWindow))
	{
		if (Input::isKeyDown(GLFW_KEY_ESCAPE))
			break;

		dt = glfwGetTime() - frameStart;
		frameStart = glfwGetTime();

		// Clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Cubes::update(dt);

		glfwSwapBuffers(window.nativeWindow);
		glfwPollEvents();
	}

	Cubes::destroy();

	glfwTerminate();
	return 0;
}