#pragma once

namespace MinecraftClone
{
	class Game
	{
	private:
		int width;
		int height;
		const char* title;

	public:
		Game(int width, int height);
		void run();
	};
}