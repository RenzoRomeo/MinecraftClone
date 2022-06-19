#include "World.h"

namespace MinecraftClone
{
	World::World(Window* window)
		: camera(Camera({ 0,0,0 }, { 0,1,0 })), renderer(Renderer(window, &camera))
	{
		defaultScene();
	}

	World::~World()
	{
	}

	void World::frame(float dt)
	{
		shader.use();

		camera.setdt(dt);
		userInput();

		for (const auto& cube : cubes)
		{
			renderer.drawCube(cube);
		}
	}

	void World::addCube(const Cube& cube)
	{
		cubes.push_back(cube);
	}

	void World::defaultScene()
	{
		for (int x = 0; x < 10; x++)
		{
			for (int z = 0; z < 10; z++)
			{
				Cube cube(glm::vec3(x - 5, 0, z - 5), { 2,3 });

				if (rand() % 10 > 8)
				{
					Cube cube(glm::vec3(x - 5, rand() % 3, z - 5), { 0, 2 });
					addCube(cube);
				}

				addCube(cube);
			}
		}
	}
	void World::userInput()
	{
		camera.processMouse(Input::xOffset, Input::yOffset);
		Input::resetMouseOffsets();

		if (Input::isKeyDown(GLFW_KEY_W))
			camera.processKeyboard(CameraMovement::FORWARD);
		if (Input::isKeyDown(GLFW_KEY_S))
			camera.processKeyboard(CameraMovement::BACKWARD);
		if (Input::isKeyDown(GLFW_KEY_A))
			camera.processKeyboard(CameraMovement::LEFT);
		if (Input::isKeyDown(GLFW_KEY_D))
			camera.processKeyboard(CameraMovement::RIGHT);
	}
}
