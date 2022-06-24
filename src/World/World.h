#pragma once

#include "../core.h"
#include "../Input.h"
#include "../Rendering/Renderer.h"
#include "Player.h"

namespace MinecraftClone
{
	class World
	{
	public:
		World(World const&) = delete;
		World& operator=(World const&) = delete;
		~World();

		static World* GetInstance();

		void Frame(Window* window);

		void GenerateNewChunks(const glm::vec3& camera_position);

		bool ChunkHasNeighbor(const glm::vec3& chunk_position, Sides side);

		void DrawChunk(Window* window, const glm::vec3& position);

		void AddCube(const Block& cube);

	private:
		Shader shader;
		Renderer renderer;
		Player player;
		int render_distance;

		std::unordered_map<glm::vec3, std::unique_ptr<Chunk>> chunk_map;

		static World* instance;

	private:
		World();

		void UserInput(float dt);
		void Falling(float dt);
		void InitChunksAroundPlayer();
	};
}