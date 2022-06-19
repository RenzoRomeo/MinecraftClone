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

		void Frame(float dt);
		void AddCube(const Cube& cube);

	private:
		void DefaultScene();
		void UserInput();
	};
}