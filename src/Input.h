#pragma once

#include "core.h"
#include "Window.h"

namespace MinecraftClone
{
	namespace Input
	{
		extern bool keyPressedData[GLFW_KEY_LAST];
		extern bool mouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST];
		extern float mouseX;
		extern float mouseY;
		extern float mouseScrollX;
		extern float mouseScrollY;
		extern bool movingLeft;
		extern bool movingRight;
		extern bool movingUp;
		extern bool movingDown;

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouseCallback(GLFWwindow* window, double xpos, double ypos);
		void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		bool isKeyDown(int key);
		bool isMouseButtonDown(int mouseButton);

		void resetMouse();
	}
}