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

		GenerateNewChunks(player.GetPosition());

		for (auto& it : chunk_map)
		{
			const glm::vec3& pos = it.first;
			auto& chunk = it.second; 
			if (chunk != nullptr && glm::length(player.GetPosition() / (float)Chunk::GetSize() - chunk->GetPosition()) <= render_distance)
			{
				DrawChunk(window, pos);
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
				chunk_map[pos] = std::make_unique<Chunk>(pos);
			}
		}
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
		// Temporal
		return false;
	}

	void World::DrawChunk(Window* window, const glm::vec3& position)
	{
		float fov = 90.0f;
		float zNear = 0.1f;
		float zFar = 10000.0f;
		glm::mat4 projection = glm::perspective(fov, window->GetAspectRatio(), zNear, zFar);

		auto& chunk = chunk_map[position];
		glm::mat4 model = glm::translate(glm::mat4(1.0f), chunk->GetPosition() * glm::vec3(Chunk::GetSize()));

		glm::mat4 view = player.GetView();

		uint32_t vertex_count = chunk->CreateMesh();

		renderer.RenderChunk(window, model, view, projection, chunk->GetVao(), vertex_count);
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
