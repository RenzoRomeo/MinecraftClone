#include "Window.h"
#include "../Input.h"

namespace MinecraftClone
{
    Window::Window(int width, int height, const char* title, bool fullscreen)
        :   window_width(width), window_height(height) {
        // GLFW window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWmonitor* primaryMonitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        native_window = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);
        if (native_window == nullptr)
        {
            std::cout << "Failed to create GLFW window.\n";
            glfwTerminate();
        }
        glfwMakeContextCurrent(native_window);
    }

    Window::~Window()
    {
        if (native_window)
            glfwDestroyWindow(native_window);
    }

    void Window::SetCallbacks()
    {
        if (native_window != nullptr)
        {
            glfwSetKeyCallback(native_window, Input::KeyCallback);
            glfwSetMouseButtonCallback(native_window, Input::MouseButtonCallback);
            glfwSetCursorPosCallback(native_window, Input::MouseCallback);
        }
    }

    void Window::Close()
    {
        if (native_window != nullptr)
            glfwSetWindowShouldClose(native_window, GLFW_TRUE);
    }
}
