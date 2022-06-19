#pragma once

#include "core.h"
#include "Input.h"
#include "Renderer.h"

namespace MinecraftClone
{
	class World
	{
	private:
		Camera camera;
		Shader shader;
		Renderer renderer;
		std::vector<Cube> cubes;

	public:
		World(Window* window);
		~World();

		void frame(float dt);
		void addCube(const Cube& cube);

	private:
		void defaultScene();
		void userInput();
	};
}