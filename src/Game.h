#pragma once

#include "Rendering/Window.h"

namespace MinecraftClone
{
	class Game
	{
	public:
		Game(int width, int height, const std::string& title);

		void Run();

	private:
		Window window;
	};
}