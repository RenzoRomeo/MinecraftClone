#include "World.h"

namespace MinecraftClone
{
	World* World::instance = nullptr;

	World::World()
		: render_distance(5)
	{
		InitChunksAroundPlayer();
	}

	World::~World()
	{
	}

	World* World::GetInstance()
	{
		if (instance == nullptr)
			instance = new World();
		return instance;
	}

	void World::Frame(Window* window, Camera* camera, float dt)
	{
		shader.Use();

		camera->SetDt(dt);

		GenerateNewChunks(camera->position);

		for (auto& it : chunk_map)
		{
			const glm::vec3& pos = it.first;
			auto& chunk = it.second; 
			if (chunk != nullptr && glm::length(camera->position / (float)Chunk::CHUNK_SIZE - chunk->position) <= render_distance)
			{
				renderer.RenderChunk(window, camera, *chunk);
			}
		}

		std::cout << "x:" << camera->position.x << " | y: " << camera->position.y << " | z: " << camera->position.z << '\r';
	}

	void World::InitChunksAroundPlayer()
	{
		int limit = render_distance;

		for (int x = -limit; x < limit; x++)
		{
			for (int z = -limit; z < limit; z++)
			{
				glm::vec3 pos = { x,0,z };
				chunk_map[pos] = std::make_unique<Chunk>(pos);
			}
		}
	}

	void World::GenerateNewChunks(const glm::vec3& camera_position)
	{
		glm::vec3 player_chunk_pos = camera_position / (float)Chunk::CHUNK_SIZE;
		for (int x = player_chunk_pos.x - render_distance; x < player_chunk_pos.x + render_distance; x++)
		{
			for (int z = player_chunk_pos.z - render_distance; z < player_chunk_pos.z + render_distance; z++)
			{
				glm::vec3 pos = { x, 0, z };
				if (chunk_map[pos] == nullptr)
				{
					chunk_map[pos] = std::make_unique<Chunk>(pos);
				}
			}
		}
	}

	bool World::ChunkHasNeighbor(const glm::vec3& chunk_position, Sides side)
	{
		// Temporal
		return false;
	}
}
