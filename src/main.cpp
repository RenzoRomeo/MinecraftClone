#include "core.h"
#include "Window.h"
#include "Input.h"
#include "Shader.h"

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

std::array<Vertex, 6>vertices1 = {
	Vertex{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
	Vertex{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
	Vertex{{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},

	Vertex{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
	Vertex{{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
	Vertex{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
};

uint32_t VBO1, VAO1;

void setUpChallenge1()
{
	glCreateVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);

	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}

void drawChallenge1()
{
	glBindVertexArray(VAO1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void destroyChallenge1()
{
	glDeleteBuffers(1, &VBO1);
	glDeleteVertexArrays(1, &VAO1);
}


std::array<Vertex, 4> vertices2 = {
	Vertex{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
	Vertex{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
	Vertex{{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
	Vertex{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
};

uint32_t indices2[6] = {
	0, 1, 2,
	0, 2, 3
};

uint32_t VAO2, VBO2, EBO2;

void setUpChallenge2()
{
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &EBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
}

void drawChallenge2()
{
	glBindVertexArray(VAO2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void destroyChallenge2()
{
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);
	glDeleteVertexArrays(1, &VAO2);
}


static std::array<Vertex, 10> vertices3 = {
	Vertex{{  -0.4f,  0.125f, 0.0f}, {  0.4f, 0.521f, 0.960f, 1.0f}},
	Vertex{{-0.125f,  0.125f, 0.0f}, {0.490f, 0.443f, 0.956f, 1.0f}},
	Vertex{{   0.0f,    0.5f, 0.0f}, {0.686f, 0.443f, 0.956f, 1.0f}},
	Vertex{{ 0.125f,  0.125f, 0.0f}, {0.917f, 0.443f, 0.956f, 1.0f}},
	Vertex{{   0.4f,  0.125f, 0.0f}, {0.807f, 0.317f, 0.250f, 1.0f}},
	Vertex{{  0.13f, -0.125f, 0.0f}, {0.807f, 0.250f, 0.682f, 1.0f}},
	Vertex{{  0.29f,   -0.6f, 0.0f}, {0.956f, 0.631f, 0.443f, 1.0f}},
	Vertex{{   0.0f,  -0.29f, 0.0f}, {0.956f, 0.843f, 0.443f, 1.0f}},
	Vertex{{ -0.29f,   -0.6f, 0.0f}, {0.862f, 0.956f, 0.443f, 1.0f}},
	Vertex{{ -0.13f, -0.125f, 0.0f}, {0.584f, 0.956f, 0.443f, 1.0f}}
};

uint32_t indices3[24] = {
	0, 1, 9,   1, 2, 3,
	3, 4, 5,   5, 6, 7,
	7, 8, 9,   9, 5, 7,
	9, 1, 3,   9, 3, 5
};

uint32_t VAO3, VBO3, EBO3;

void setUpChallenge3()
{
	glCreateVertexArrays(1, &VAO3);
	glBindVertexArray(VAO3);

	glCreateBuffers(1, &VBO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glCreateBuffers(1, &EBO3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);
}

void drawChallenge3()
{
	glBindVertexArray(VAO3);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
}

void destroyChallenge3()
{
	glDeleteVertexArrays(1, &VAO3);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &EBO3);
}


std::array<Vertex, 4> vertices4 = {
	Vertex{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
	Vertex{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
	Vertex{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
	Vertex{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
};

uint32_t indices4[] = {
	0, 1,	1, 2,
	2, 3,	3, 0
};

uint32_t VAO4, VBO4, EBO4;

void setUpChallenge4()
{
	glCreateVertexArrays(1, &VAO4);
	glBindVertexArray(VAO4);

	glCreateBuffers(1, &VBO4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glCreateBuffers(1, &EBO4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);
}

void drawChallenge4()
{
	glBindVertexArray(VAO4);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
}

void destroyChallenge4()
{
	glDeleteVertexArrays(1, &VAO4);
	glDeleteBuffers(1, &VBO4);
	glDeleteBuffers(1, &EBO4);
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

	setUpChallenge4();
	
	glViewport(0, 0, window.windowWidth, window.windowHeight);
	while (!glfwWindowShouldClose(window.nativeWindow))
	{
		// Clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (Input::isKeyDown(GLFW_KEY_E))
			std::cout << "E\n.";

		shader.use();

		drawChallenge4();

		glfwSwapBuffers(window.nativeWindow);
		glfwPollEvents();
	}

	destroyChallenge4();
	glfwTerminate();
	return 0;
}