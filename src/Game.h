#pragma once

#include "Rendering/Renderer.h"

namespace MinecraftClone
{
	class Game
	{
	private:
		int width;
		int height;
		const char* title;
		Window window;
		Camera camera;

	public:
		Game(int width, int height);
		void Run();

	private:
		void UserInput();
	};
}