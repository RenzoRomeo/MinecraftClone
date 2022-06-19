#include "World.h"

namespace MinecraftClone
{
	World::World(Window* window)
		: camera(Camera({ 0,0,0 }, { 0,1,0 })), renderer(Renderer(window, &camera))
	{
		DefaultScene();
	}

	World::~World()
	{
	}

	void World::Frame(float dt)
	{
		shader.use();

		camera.SetDt(dt);
		UserInput();

		for (const auto& cube : cubes)
		{
			renderer.drawCube(cube);
		}
	}

	void World::AddCube(const Cube& cube)
	{
		cubes.push_back(cube);
	}

	void World::DefaultScene()
	{
		for (int x = 0; x < 10; x++)
		{
			for (int z = 0; z < 10; z++)
			{
				Cube cube(glm::vec3(x - 5, 0, z - 5), { 1,1 });

				if (rand() % 10 > 8)
				{
					Cube cube(glm::vec3(x - 5, rand() % 3, z - 5), { 0, 1 });
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
			camera.ProcessKeyboard(CameraMovement::FORWARD);
		if (Input::IsKeyDown(GLFW_KEY_S))
			camera.ProcessKeyboard(CameraMovement::BACKWARD);
		if (Input::IsKeyDown(GLFW_KEY_A))
			camera.ProcessKeyboard(CameraMovement::LEFT);
		if (Input::IsKeyDown(GLFW_KEY_D))
			camera.ProcessKeyboard(CameraMovement::RIGHT);
	}
}
