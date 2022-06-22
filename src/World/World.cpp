#include "World.h"

namespace MinecraftClone
{
	World::World(Window* window)
		: camera(Camera({ 0,0,0 }, { 0,1,0 })), renderer(Renderer(window, &camera))
	{
		// DefaultScene();
		chunks.push_back(new Chunk());
	}

	World::~World()
	{
		for (auto& chunk : chunks)
		{
			delete chunk;
		}
	}

	void World::Frame(float dt)
	{
		shader.use();

		camera.SetDt(dt);
		UserInput();

		for (const auto& chunk : chunks)
		{
			renderer.RenderChunk(*chunk);
		}
		// for (const auto& cube : cubes)
		// {
		// 	renderer.DrawCube(cube);
		// }
	}

	void World::AddCube(const Block& cube)
	{
		cubes.push_back(cube);
	}

	void World::DefaultScene()
	{
		for (int x = 0; x < 10; x++)
		{
			for (int z = 0; z < 10; z++)
			{
				Block cube(glm::vec3(x - 5, 0, z - 5), { 1,1 });

				if (rand() % 10 > 8)
				{
					Block cube(glm::vec3(x - 5, rand() % 3, z - 5), { 0, 1 });
					AddCube(cube);
				}

				AddCube(cube);
			}
		}
	}
	void World::UserInput()
	{
		camera.ProcessMouse(Input::x_offset, Input::y_offset);
		Input::ResetMouseOffsets();

		if (Input::IsKeyDown(GLFW_KEY_W))
			camera.ProcessKeyboard(CameraMovement::Forward);
		if (Input::IsKeyDown(GLFW_KEY_S))
			camera.ProcessKeyboard(CameraMovement::Backward);
		if (Input::IsKeyDown(GLFW_KEY_A))
			camera.ProcessKeyboard(CameraMovement::Left);
		if (Input::IsKeyDown(GLFW_KEY_D))
			camera.ProcessKeyboard(CameraMovement::Right);
	}
}
