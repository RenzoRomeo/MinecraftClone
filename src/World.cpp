#include "World.h"

namespace MinecraftClone
{
	World::World(Window* window)
		: camera(Camera()), renderer(Renderer(window, &camera))
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
				Cube cube(glm::vec3(x - 5, 0, z - 5), { 2,2 });

				if (rand() % 10 > 8)
				{
					Cube cube(glm::vec3(x - 5, rand() % 3, z - 5), { 0, 3 });
					addCube(cube);
				}

				addCube(cube);
			}
		}
	}
	void World::userInput()
	{
		if (Input::movingUp)
			camera.rotateUp();
		if (Input::movingDown)
			camera.rotateDown();
		if (Input::movingLeft)
			camera.rotateLeft();
		if (Input::movingRight)
			camera.rotateRight();

		Input::resetMouse();

		if (Input::isKeyDown(GLFW_KEY_W))
			camera.moveForward();
		if (Input::isKeyDown(GLFW_KEY_S))
			camera.moveBackwards();
		if (Input::isKeyDown(GLFW_KEY_A))
			camera.moveLeft();
		if (Input::isKeyDown(GLFW_KEY_D))
			camera.moveRight();
	}
}
