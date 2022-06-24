#include "core.h"
#include "Input.h"
#include "Game.h"
#include "World/World.h"

namespace MinecraftClone
{
	Game::Game(int width, int height, const std::string& title)
		: window(Window(width, height, title.c_str()))
	{
	}

	void Game::Run()
	{
		World* world = World::GetInstance();

		while (!window.ShouldClose())
		{
			if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
				break;

			window.Clear(135.0f, 206.0f, 235.0f);

			world->Frame(&window);

			window.SwapBuffers();
			window.PollEvents();
		}
	}
}