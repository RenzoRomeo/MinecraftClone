#pragma once

#include "../core.h"
#include "../Input.h"
#include "../Rendering/Renderer.h"

namespace MinecraftClone
{
	class World
	{
	private:
		Camera camera;
		Shader shader;
		Renderer renderer;
		std::vector<Chunk*> chunks;

	public:
		World(Window* window);
		~World();

		void Frame(float dt);
		void AddCube(const Block& cube);

	private:
		void UserInput();
		//void GenerateChunksAroundPlayer();
	};
}