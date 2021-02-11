#include "Systems/renderSystem.hpp"

#include <vector>

#include "Maths/extendedTypes.hpp"

#include "Components/transform.hpp"
#include "Components/camera.hpp"
#include "Components/meshRenderer.hpp"

void RenderSystem::Init(ECSManager& _ecsManager)
{
    shader.InitProgram(
        // Vertex shader
        R"GLSL(
        #version 330

        layout (location = 0) in vec3 inPos;
        layout (location = 1) in vec3 inNormal;

        uniform mat4 uModel;
        uniform mat4 uView;
        uniform mat4 uProjection;

        out vec3 normal;
        out vec3 fragPosWorld;

        void main()
        {
            fragPosWorld = vec3(uModel * vec4(inPos, 1.0));
            normal = mat3(uModel) * inNormal;

            gl_Position = uProjection * uView * uModel * vec4(inPos, 1.0f);
        }
        )GLSL",

        // Fragment shader
        R"GLSL(
        #version 330

        out vec4 FragColor;

        in vec3 normal;
        in vec3 fragPosWorld;

        uniform vec3 uColor;

        vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

        vec3 lightPos = vec3(-100.0f, 50.0f, 100.0f);

        void main()
        {
            // Ambient
            float ambientStrength = 0.5;
            vec3 ambient = ambientStrength * lightColor;

            // Diffuse
            vec3 norm = normalize(normal);
            vec3 lightDir = normalize(lightPos - fragPosWorld);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;


            vec3 result = (ambient + diffuse) * uColor;
            FragColor = vec4(result, 1.0);
        }
        )GLSL"
        );

    camera = _ecsManager.CreateEntity();

    _ecsManager.AddComponent(camera,Transform{
            {0.f,0.f,150.f}
    });

    _ecsManager.AddComponent(camera, Camera
            {Camera::MakeProjectionTransform(DegToRad(45.0f),0.01f,1000.0f,1280,720)}
    );

    std::vector<Float3> vertices =
            {
                    Float3{-0.5f, -0.5f, -0.5f},
                    Float3{0.5f, -0.5f, -0.5f},
                    Float3{0.5f, 0.5f, -0.5f},
                    Float3{0.5f, 0.5f, -0.5f},
                    Float3{-0.5f, 0.5f, -0.5f},
                    Float3{-0.5f, -0.5f, -0.5f},
                    Float3{-0.5f, -0.5f, 0.5},
                    Float3{0.5f, -0.5f, 0.5},
                    Float3{0.5f, 0.5f, 0.5},
                    Float3{0.5f, 0.5f, 0.5},
                    Float3{-0.5f, 0.5f, 0.5},
                    Float3{-0.5f, -0.5f, 0.5},
                    Float3{-0.5f, 0.5f, 0.5f},
                    Float3{-0.5f, 0.5f, -0.5f},
                    Float3{-0.5f, -0.5f, -0.5f},
                    Float3{-0.5f, -0.5f, -0.5f},
                    Float3{-0.5f, -0.5f, 0.5f},
                    Float3{-0.5f, 0.5f, 0.5f},
                    Float3{0.5f, 0.5f, 0.5},
                    Float3{0.5f, 0.5f, -0.5},
                    Float3{0.5f, -0.5f, -0.5},
                    Float3{0.5f, -0.5f, -0.5},
                    Float3{0.5f, -0.5f, 0.5},
                    Float3{0.5f, 0.5f, 0.5},
                    Float3{-0.5f, -0.5f, -0.5f},
                    Float3{0.5f, -0.5f, -0.5f},
                    Float3{0.5f, -0.5f, 0.5f},
                    Float3{0.5f, -0.5f, 0.5f},
                    Float3{-0.5f, -0.5f, 0.5f},
                    Float3{-0.5f, -0.5f, -0.5f},
                    Float3{-0.5f, 0.5f, -0.5},
                    Float3{0.5f, 0.5f, -0.5},
                    Float3{0.5f, 0.5f, 0.5},
                    Float3{0.5f, 0.5f, 0.5},
                    Float3{-0.5f, 0.5f, 0.5},
                    Float3{-0.5f, 0.5f, -0.5}
            };

    std::vector<Float3> normals =
            {
                    Float3{0.0f, 0.0f, -1.0f},
                    Float3{0.0f, 0.0f, -1.0f},
                    Float3{0.0f, 0.0f, -1.0f},
                    Float3{0.0f, 0.0f, -1.0f},
                    Float3{0.0f, 0.0f, -1.0f},
                    Float3{0.0f, 0.0f, -1.0f},
                    Float3{0.0f, 0.0f, 1.0f},
                    Float3{0.0f, 0.0f, 1.0f},
                    Float3{0.0f, 0.0f, 1.0f},
                    Float3{0.0f, 0.0f, 1.0f},
                    Float3{0.0f, 0.0f, 1.0f},
                    Float3{0.0f, 0.0f, 1.0f},
                    Float3{-1.0f, 0.0f, 0.0f},
                    Float3{-1.0f, 0.0f, 0.0f},
                    Float3{-1.0f, 0.0f, 0.0f},
                    Float3{-1.0f, 0.0f, 0.0f},
                    Float3{-1.0f, 0.0f, 0.0f},
                    Float3{-1.0f, 0.0f, 0.0f},
                    Float3{1.0f, 0.0f, 0.0f},
                    Float3{1.0f, 0.0f, 0.0f},
                    Float3{1.0f, 0.0f, 0.0f},
                    Float3{1.0f, 0.0f, 0.0f},
                    Float3{1.0f, 0.0f, 0.0f},
                    Float3{1.0f, 0.0f, 0.0f},
                    Float3{0.0f, -1.0f, 0.0f},
                    Float3{0.0f, -1.0f, 0.0f},
                    Float3{0.0f, -1.0f, 0.0f},
                    Float3{0.0f, -1.0f, 0.0f},
                    Float3{0.0f, -1.0f, 0.0f},
                    Float3{0.0f, -1.0f, 0.0f},
                    Float3{0.0f, 1.0f, 0.0f},
                    Float3{0.0f, 1.0f, 0.0f},
                    Float3{0.0f, 1.0f, 0.0f},
                    Float3{0.0f, 1.0f, 0.0f},
                    Float3{0.0f, 1.0f, 0.0f},
                    Float3{0.0f, 1.0f, 0.0}
            };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertices
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Float3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Float3), (void*)nullptr);
    glEnableVertexAttribArray(0);

    // Surface normal
    glGenBuffers(1, &normal);
    glBindBuffer(GL_ARRAY_BUFFER, normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Float3) * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Float3), (void*)nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void RenderSystem::Update(float _deltaTime, ECSManager &_ecsManager)
{
    glClearColor(0.f,0.f,0.f,1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.Activate();
    glBindVertexArray(vao);

    auto& cameraTransform = _ecsManager.GetComponent<Transform>(camera);
    auto& ccamera          = _ecsManager.GetComponent<Camera>(camera);

    for(auto entity : entities)
    {
        const auto& transform = _ecsManager.GetComponent<Transform>(entity);
        const auto& mesh = _ecsManager.GetComponent<MeshRenderer>(entity);

        Mat4 view;
        view.e[12] = -cameraTransform.position.x;
        view.e[13] = -cameraTransform.position.y;
        view.e[14] = -cameraTransform.position.z;

        Mat4 rotY;

        float cos_theta_y = cosf(transform.rotation.y);
        float sin_theta_y = sinf(transform.rotation.y);

        rotY.e[0] = cos_theta_y;
        rotY.e[2] = -sin_theta_y;
        rotY.e[8] = sin_theta_y;
        rotY.e[10] = cos_theta_y;

        Mat4 rotX;

        float cosThetaX = cosf(transform.rotation.x);
        float sinThetaX = sinf(transform.rotation.x);

        rotX.e[5] = cosThetaX;
        rotX.e[6] = sinThetaX;
        rotX.e[9] = -sinThetaX;
        rotX.e[10]= cosThetaX;

        Mat4 rotZ;

        float cosThetaZ = cosf(transform.rotation.z);
        float sinThetaZ = sinf(transform.rotation.z);

        rotZ.e[0] = cosThetaZ;
        rotZ.e[1] = sinThetaZ;
        rotZ.e[4] = -sinThetaZ;
        rotZ.e[5] = cosThetaZ;

        Mat4 translate;
        translate.e[12] = transform.position.x;
        translate.e[13] = transform.position.y;
        translate.e[14] = transform.position.z;

        Mat4 scaleMat;
        scaleMat.e[0]  = transform.scale.x;
        scaleMat.e[5]  = transform.scale.y;
        scaleMat.e[10] = transform.scale.z;

        Mat4 model = translate * scaleMat * rotY;

        Mat4 projection = ccamera.projection;

        shader.SetUniform<Mat4>("uModel", model);
        shader.SetUniform<Mat4>("uView", view);
        shader.SetUniform<Mat4>("uProjection", projection);
        shader.SetUniform<Float3>("uColor", mesh.color);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}
