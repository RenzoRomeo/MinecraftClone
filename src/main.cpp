#include "core.h"
#include "Window.h"
#include "Input.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

struct Vertex
{
	std::array<float, 3> position;
	std::array<float, 4> color;
};

std::array<Vertex, 4> sVertices = {
	Vertex{{-10.0f, -10.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
	Vertex{{ 10.0f, -10.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
	Vertex{{ 10.0f,  10.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
	Vertex{{-10.0f,  10.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
};

uint32_t sIndices[6] = {
	0, 1, 2,
	0, 2, 3
};

uint32_t sVAO, sVBO, sEBO;

void setupSquare()
{
	glCreateVertexArrays(1, &sVAO);
	glBindVertexArray(sVAO);

	glCreateBuffers(1, &sVBO);
	glBindBuffer(GL_ARRAY_BUFFER, sVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sVertices), sVertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glCreateBuffers(1, &sEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sIndices), sIndices, GL_STATIC_DRAW);
}

void drawSquare()
{
	glBindVertexArray(sVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

	Shader shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");

	setupSquare();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(10.0f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(2.0f, 2.0f, 0.0f));

	glm::vec3 eye = glm::vec3(0.0f, 0.0f, 20.0f);
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(eye, center, up);

	float projW = 1920.0f;
	float windowAspect = ((float)window.windowWidth / (float)window.windowHeight);
	float projH = projW / windowAspect;

	float left = -projW / 2.0f;
	float right = projW / 2.0f;
	float bottom = -projH / 2.0f;
	float top = projH / 2.0f;
	float near = 0.0001f;
	float far = 10000.0f;

	glm::mat4 projection = glm::ortho(left, right, bottom, top, near, far);

	shader.setUniformMat4f("uModel", model);
	shader.setUniformMat4f("uView", view);
	shader.setUniformMat4f("uProjection", projection);

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	
	glViewport(0, 0, window.windowWidth, window.windowHeight);
	while (!glfwWindowShouldClose(window.nativeWindow))
	{
		// Clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (Input::isKeyDown(GLFW_KEY_D))
			x += 0.1f;
		else if (Input::isKeyDown(GLFW_KEY_A))
			x -= 0.1f;
		else if (Input::isKeyDown(GLFW_KEY_W))
			y += 0.1f;
		else if (Input::isKeyDown(GLFW_KEY_S))
			y -= 0.1f;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(10.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(x, y, z));

		shader.use();
		shader.setUniformMat4f("uModel", model);

		drawSquare();

		glfwSwapBuffers(window.nativeWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}