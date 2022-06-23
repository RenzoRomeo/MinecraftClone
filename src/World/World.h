#pragma once

#include "../core.h"
#include "../Input.h"
#include "../Rendering/Renderer.h"

namespace MinecraftClone
{
	class World
	{
	private:
		Shader shader;
		Renderer renderer;
		int render_distance;

		std::unordered_map<glm::vec3, std::unique_ptr<Chunk>> chunk_map;

		static World* instance;

	public:
		World(World const&) = delete;
		World& operator=(World const&) = delete;
		~World();

		static World* GetInstance();

		void Frame(Window* window, Camera* camera, float dt);

		void GenerateNewChunks(const glm::vec3& camera_position);

		bool ChunkHasNeighbor(const glm::vec3& chunk_position, Sides side);

		void AddCube(const Block& cube);

	private:
		World();

		void InitChunksAroundPlayer();
	};
}