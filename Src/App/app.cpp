#include "App/app.hpp"

#include <stdexcept>
#include <iostream>
#include <random>

#include "Components/gravity.hpp"
#include "Components/transform.hpp"
#include "Components/rigidbody.hpp"
#include "Components/meshRenderer.hpp"
#include "Components/camera.hpp"

App::App()
{
    window.CreateWindow("ECS",{1280,720});

    InitOpenGL();
    InitECS();

    Loop();
}

void App::InitOpenGL()
{
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        throw std::runtime_error("Failed to load glad !");

    if (GLAD_GL_KHR_debug)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(GLDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 0, nullptr, GL_FALSE);
    }
}

void App::InitECS()
{
    ecsManager.Init();

    ecsManager.RegisterComponent<Transform>();
    ecsManager.RegisterComponent<Rigidbody>();
    ecsManager.RegisterComponent<Gravity>();
    ecsManager.RegisterComponent<MeshRenderer>();
    ecsManager.RegisterComponent<Camera>();

    physicsSystem = ecsManager.RegisterSystem<PhysicsSystem>();
    {
        Signature signature;
        signature.set(ecsManager.GetComponentType<Transform>());
        signature.set(ecsManager.GetComponentType<Rigidbody>());
        signature.set(ecsManager.GetComponentType<Gravity>());
        ecsManager.SetSystemSignature<PhysicsSystem>(signature);
    }

    renderSystem = ecsManager.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(ecsManager.GetComponentType<MeshRenderer>());
        signature.set(ecsManager.GetComponentType<Transform>());
        ecsManager.SetSystemSignature<RenderSystem>(signature);
    }
    renderSystem->Init(ecsManager);
}

App::~App()
{
}

void App::Loop()
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
    std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
    std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
    std::uniform_real_distribution<float> randColor(0.0f, 1.0f);

    // Init demo scene
    for (size_t i = 0; i < 500 ; ++i)
    {
        Entity entity = ecsManager.CreateEntity();

        ecsManager.AddComponent(entity,Gravity{
            {0.f,0.f,0.f}
        });

        ecsManager.AddComponent(entity,
                                Rigidbody{
            {0.f,0.f,0.f},
            {0.f,0.f,0.f}
        });

        ecsManager.AddComponent(entity,Transform{
                {randPosition(generator),randPosition(generator),randPosition(generator)},
                {randRotation(generator),randRotation(generator),randRotation(generator)},
                {randScale(generator),randScale(generator),randScale(generator)}
        });

        ecsManager.AddComponent(entity,MeshRenderer{
                {randColor(generator),randColor(generator),randColor(generator)}
        });
    }

    float deltaTime = 0;
    float lastTime = 0;

    while (!glfwWindowShouldClose(window.GetHandle()))
    {
        glfwPollEvents();

        window.update();

        physicsSystem->Update(deltaTime,ecsManager);
        renderSystem->Update(deltaTime,ecsManager);

        glfwSwapBuffers(window.GetHandle());

        float currTime = glfwGetTime();
        deltaTime =  currTime - lastTime;
        lastTime = currTime;
    }
}

void App::GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                          const void *userParam)
{
    std::cout << "OpenGL Debug : " << message << std::endl;
}
