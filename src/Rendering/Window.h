#pragma once

#include "../core.h"

namespace MinecraftClone
{
	class Window
	{
	public:
		Window(int width, int height, const char* title, bool fullscreen = false);

		~Window();

		void Close();
		bool ShouldClose();
		void SwapBuffers();
		void PollEvents();
		void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

		int GetWidth() const { return window_width; }
		int GetHeight() const { return window_height; }
		float GetAspectRatio() const { return (float)window_width / (float)window_height; }

	private:
		GLFWwindow* native_window;
		int window_width;
		int window_height;

	private:
		void SetCallbacks();
	};
}