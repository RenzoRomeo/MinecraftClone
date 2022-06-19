#include "Input.h"

namespace MinecraftClone
{
    namespace Input
    {
        bool key_pressed_data[GLFW_KEY_LAST] = {};
        bool mouse_button_pressed_data[GLFW_MOUSE_BUTTON_LAST] = {};
        float mouse_x = 0.0f;
        float mouse_y = 0.0f;
        float mouse_scroll_x = 0.0f;
        float mouse_scroll_y = 0.0f;
        float x_offset = 0.0f;
        float y_offset = 0.0f;

        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key >= 0 && key < GLFW_KEY_LAST)
                key_pressed_data[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
        }

        void MouseCallback(GLFWwindow* window, double xpos, double ypos)
        {
            x_offset = xpos - mouse_x;
            y_offset = mouse_y - ypos;

            mouse_x = (float)xpos;
            mouse_y = (float)ypos;
        }

        void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
        {
            if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
                mouse_button_pressed_data[button] = action == GLFW_PRESS;
        }

        void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
        {
            mouse_scroll_x = (float)xoffset;
            mouse_scroll_y = (float)yoffset;
        }

        bool IsKeyDown(int key)
        {
            if (key >= 0 && key < GLFW_KEY_LAST)
                return key_pressed_data[key];

            return false;
        }

        bool IsMouseButtonDown(int mouseButton)
        {
            if (mouseButton >= 0 && mouseButton < GLFW_MOUSE_BUTTON_LAST)
                return mouse_button_pressed_data[mouseButton];

            return false;
        }

        void ResetMouseOffsets() {
            x_offset = 0.0f;
            y_offset = 0.0f;
        }
    }
}
