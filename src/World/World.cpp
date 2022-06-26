#include "World.h"

namespace MinecraftClone
{
	World* World::instance = nullptr;

	World::World()
		: render_distance(5), player(Player())
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

	void World::Frame(Window* window)
	{
		static float frameStart = glfwGetTime();
		static float dt = 0.0f;

		dt = glfwGetTime() - frameStart;
		frameStart = glfwGetTime();

		UserInput(dt);

		// Procedural generation
		GenerateNewChunks(player.GetPosition());

		for (auto& it : chunk_map)
		{
			const glm::vec3& pos = it.first;
			auto& chunk = it.second;
			if (chunk != nullptr && glm::length(player.GetPosition() / (float)Chunk::GetSize() - chunk->GetPosition()) <= render_distance)
			{
				renderer.RenderChunk(window, *chunk, player);
			}
		}

		// Falling(dt);

		std::cout << "x:" << player.GetPosition().x << " | y: " << player.GetPosition().y << " | z: " << player.GetPosition().z << '\r';
	}

	void World::InitChunksAroundPlayer()
	{
		int limit = render_distance;

		for (int x = -limit; x < limit; x++)
		{
			for (int z = -limit; z < limit; z++)
			{
				glm::vec3 pos = { x,0,z };
				chunk_map[pos] = std::make_shared<Chunk>(pos);
			}
		}

		chunk_map[{0, 0, 0}]->SetEmpty();
		chunk_map[{0,1,0}] = std::make_shared<Chunk>(glm::vec3{0,1,0});
	}

	void World::GenerateNewChunks(const glm::vec3& camera_position)
	{
		glm::vec3 player_chunk_pos = camera_position / (float)Chunk::GetSize();
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
		if (side == Sides::Top)
			return chunk_map[{chunk_position.x, chunk_position.y + 1, chunk_position.z}] != nullptr;

		if (side == Sides::Bottom)
			return chunk_map[{chunk_position.x, chunk_position.y - 1, chunk_position.z}] != nullptr;

		if (side == Sides::Left)
			return chunk_map[{chunk_position.x - 1, chunk_position.y, chunk_position.z}] != nullptr;

		if (side == Sides::Right)
			return chunk_map[{chunk_position.x + 1, chunk_position.y, chunk_position.z}] != nullptr;

		if (side == Sides::Back)
			return chunk_map[{chunk_position.x, chunk_position.y, chunk_position.z - 1}] != nullptr;

		if (side == Sides::Front)
			return chunk_map[{chunk_position.x, chunk_position.y, chunk_position.z + 1}] != nullptr;

		return false;
	}

	std::shared_ptr<Chunk> World::NeighboringChunk(const glm::vec3 chunk_position, Sides side)
	{
		if (side == Sides::Top)
			return chunk_map[{chunk_position.x, chunk_position.y + 1, chunk_position.z}];

		if (side == Sides::Bottom)
			return chunk_map[{chunk_position.x, chunk_position.y - 1, chunk_position.z}];

		if (side == Sides::Left)
			return chunk_map[{chunk_position.x - 1, chunk_position.y, chunk_position.z}];

		if (side == Sides::Right)
			return chunk_map[{chunk_position.x + 1, chunk_position.y, chunk_position.z}];

		if (side == Sides::Back)
			return chunk_map[{chunk_position.x, chunk_position.y, chunk_position.z - 1}];

		if (side == Sides::Front)
			return chunk_map[{chunk_position.x, chunk_position.y, chunk_position.z + 1}];
	}

	std::shared_ptr<Chunk> World::GetChunk(const glm::vec3& chunk_position)
	{
		return chunk_map[chunk_position];
	}

	bool World::IsNeighborSolidBlock(const glm::vec3& chunk_position, const glm::vec3& block_position, Sides side)
	{
		if (!ChunkHasNeighbor(chunk_position, side))
			return false;

		std::shared_ptr<Chunk> chunk = NeighboringChunk(chunk_position, side);

		if (side == Sides::Top)
			return chunk->GetBlock(block_position.x, 0, block_position.z).solid;

		if (side == Sides::Bottom)
			return chunk->GetBlock(block_position.x, Chunk::GetSize() - 1, block_position.z).solid;

		if (side == Sides::Left)
			return chunk->GetBlock(Chunk::GetSize() - 1, block_position.y, block_position.z).solid;

		if (side == Sides::Right)
			return chunk->GetBlock(0, block_position.y, block_position.z).solid;

		if (side == Sides::Back)
			return chunk->GetBlock(block_position.x, block_position.y, Chunk::GetSize() - 1).solid;

		if (side == Sides::Front)
			return chunk->GetBlock(block_position.x, block_position.y, 0).solid;

		return false;
	}

	void World::UserInput(float dt)
	{
		player.ProcessMouse(Input::x_offset, Input::y_offset, dt);
		Input::ResetMouseOffsets();

		if (Input::IsKeyDown(GLFW_KEY_W))
			player.ProcessKeyboard(Movement::Forward, dt);
		if (Input::IsKeyDown(GLFW_KEY_S))
			player.ProcessKeyboard(Movement::Backward, dt);
		if (Input::IsKeyDown(GLFW_KEY_A))
			player.ProcessKeyboard(Movement::Left, dt);
		if (Input::IsKeyDown(GLFW_KEY_D))
			player.ProcessKeyboard(Movement::Right, dt);
		if (Input::IsKeyDown(GLFW_KEY_SPACE))
			player.ProcessKeyboard(Movement::Jump, dt);
	}

	void World::Falling(float dt)
	{
		static glm::vec3 g = { 0, -2, 0 };

		const glm::vec3& player_position = player.GetPosition();

		if (player_position.y != 5 && player_position.y > player.GetHeight())
		{
			player.SetPosition(player_position + player.GetVelocity());
			player.SetVelocity(player.GetVelocity() + g * dt);
		}
		else
		{
			player.SetPosition({ player_position.x,5,player_position.z });
			player.SetVelocity({ 0,0,0 });
		}
	}
}
