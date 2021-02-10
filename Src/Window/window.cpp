#include "Window/window.hpp"

#include <stdexcept>
#include <iostream>

Window::~Window()
{
    if(window != nullptr)
        glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::GLFWErrorCallback(int error_code, const char *description)
{
    std::cout << "GLFW Error : (" << error_code << ") " << description << std::endl;
}

void Window::CreateWindow(const char* _title, Int2 _size)
{
    if(!glfwInit())
        throw std::runtime_error("GLFW initialisation failed !");

    glfwSetErrorCallback(GLFWErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(_size.x,_size.y,_title, nullptr, nullptr);

    if(window == nullptr)
        throw std::runtime_error("GLFW create window failed !");

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // !v-sync
}

void Window::update()
{
    glfwGetWindowSize(window,&windowSize.x, &windowSize.y);
}

GLFWwindow* Window::GetHandle() const
{
    return window;
}

Int2 Window::GetWindowSize() const
{
    return windowSize;
}
