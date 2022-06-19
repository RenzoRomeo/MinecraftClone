#pragma once

#include "Shader.h"
#include "Window.h"
#include "Cube.h"
#include "Camera.h"
#include "Textures.h"

namespace MinecraftClone
{
	class Renderer
	{
	private:
		Camera* camera;
		Shader shader;
		Window* window;
		uint32_t VAO, VBO;

		int atlasW, atlasH, spriteSize;
		uint32_t atlasID;
		std::array<Vertex, 36> cubeVertices;

		glm::mat4 projection;

	public:
		Renderer(Window* window, Camera* camera);
		~Renderer();

		void drawCube(const Cube& cube);

	private:
		void loadAtlas(const std::string& path, int& width, int& height);
	};
}