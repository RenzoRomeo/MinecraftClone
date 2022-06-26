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

		std::shared_ptr<Chunk> GetChunk(const glm::vec3& chunk_position);

		bool IsNeighborSolidBlock(const glm::vec3& chunk_position, const glm::vec3& block_position, Sides side);

		void AddCube(const Block& cube);

		static glm::vec3 GetVx() { return { 1,0,0 }; }
		static glm::vec3 GetVy() { return { 0,1,0 }; }
		static glm::vec3 GetVz() { return { 0,0,1 }; }

	private:
		static World* instance;

		Shader shader;
		Renderer renderer;
		Player player;
		int render_distance;

		std::unordered_map<glm::vec3, std::shared_ptr<Chunk>> chunk_map;

	private:
		World();

		void UserInput(float dt);
		void Falling(float dt);
		void InitChunksAroundPlayer();
		bool ChunkHasNeighbor(const glm::vec3& chunk_position, Sides side);
		std::shared_ptr<Chunk> NeighboringChunk(const glm::vec3 chunk_position, Sides side);
	};
}