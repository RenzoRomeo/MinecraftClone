#include "Window.h"
#include "Input.h"

namespace MinecraftClone
{
    Window::Window(int width, int height, const char* title, bool fullscreen) {
        // GLFW window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWmonitor* primaryMonitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        nativeWindow = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);
        if (nativeWindow == nullptr)
        {
            std::cout << "Failed to create GLFW window.\n";
            glfwTerminate();
        }
        glfwMakeContextCurrent(nativeWindow);
    }

    Window::~Window()
    {
        if (nativeWindow)
            glfwDestroyWindow(nativeWindow);
    }

    void Window::setCallbacks()
    {
        if (nativeWindow != nullptr)
        {
            glfwSetKeyCallback(nativeWindow, Input::keyCallback);
            glfwSetMouseButtonCallback(nativeWindow, Input::mouseButtonCallback);
            glfwSetCursorPosCallback(nativeWindow, Input::mouseCallback);
        }
    }

    void Window::close()
    {
        if (nativeWindow != nullptr)
            glfwSetWindowShouldClose(nativeWindow, GLFW_TRUE);
    }
}
