#pragma once

#include "core.h"
#include "Camera.h"
#include "Input.h"
#include "Shader.h"
#include "Window.h"
#include "Cube.h"

namespace MinecraftClone
{
	class World
	{
	private:
		Camera camera;
		Shader shader;
		Window* window;
		uint32_t VAO, VBO;

		std::vector<Texture> textures;
		std::array<Vertex, 36> cubeVertices;

		glm::mat4 projection;

		std::vector<Cube> cubes;

	public:
		World(Window* window);
		~World();

		void frame(float dt);
		void addCube(const Cube& cube);

	private:
		void drawCube(const Cube& cube);
		Texture createTexture(const std::string& filepath, bool pixelated = false);
		void defaultScene();
		void userInput();
	};
}