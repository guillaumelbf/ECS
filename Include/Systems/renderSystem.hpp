#pragma once

#include <glad/glad.h>

#include "ECS/system.hpp"
#include "ECS/ecsManager.hpp"
#include "Shader/shader.hpp"

class RenderSystem : public System
{
private:
    Shader shader;

    Entity camera;

    GLuint vao;
    GLuint vbo;
    GLuint normal;
public:
    void Init(ECSManager& _ecsManager);

    void Update(float _deltaTime, ECSManager& _ecsManager);
};
