#pragma once

#include <glad/glad.h>

#include "Window/window.hpp"
#include "ECS/ecsManager.hpp"
#include "Systems/physicsSystem.hpp"
#include "Systems/renderSystem.hpp"
#include "App/fps.hpp"

class App
{
private:
    Window window;

    Fps fps;
    ECSManager ecsManager;

    std::shared_ptr<PhysicsSystem> physicsSystem;
    std::shared_ptr<RenderSystem> renderSystem;

    void InitOpenGL();
    void InitECS();

    void Loop();

    static void GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam);
public:

    App();
    ~App();
};
