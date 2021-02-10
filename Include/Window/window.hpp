#pragma once

#include <GLFW/glfw3.h>

#include "Maths/extendedTypes.hpp"

class Window
{
private:
    GLFWwindow* window;
    Int2 windowSize;

    static void GLFWErrorCallback(int error_code, const char* description);

public:

    ~Window();

    void CreateWindow(const char* _title, Int2 _size);

    void update();

    [[nodiscard]]
    GLFWwindow* GetHandle() const;

    [[nodiscard]]
    Int2 GetWindowSize() const;
};
