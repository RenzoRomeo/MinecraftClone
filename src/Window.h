#pragma once

#include "core.h"

namespace MinecraftClone
{
	struct Window
	{
		Window(int width, int height, const char* title, bool fullscreen = false);
		~Window();

		GLFWwindow* nativeWindow;
		int windowWidth;
		int windowHeight;

		void setCallbacks();
		void close();

		static Window* createWindow(int width, int height, const char* title, bool fullscreen = false);
		static void freeWindow(Window* window);
	};
}