#include "Window.h"
#include "Input.h"

namespace MinecraftClone
{
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

    Window* Window::createWindow(int width, int height, const char* title, bool fullscreen)
    {
        // GLFW window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        Window* res = new Window();
        GLFWmonitor* primaryMonitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        res->nativeWindow = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);
        if (res->nativeWindow == nullptr)
        {
            std::cout << "Failed to create GLFW window.\n";
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(res->nativeWindow);

        return res;
    }

    void Window::freeWindow(Window* window)
    {
        if (window)
        {
            glfwDestroyWindow(window->nativeWindow);
            delete window;
        }
    }
}
