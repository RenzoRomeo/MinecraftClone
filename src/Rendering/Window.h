#pragma once

#include "../core.h"

namespace MinecraftClone
{
	struct Window
	{
		Window(int width, int height, const char* title, bool fullscreen = false);
		~Window();

		GLFWwindow* native_window;
		int window_width;
		int window_height;

		void SetCallbacks();
		void Close();
	};
}