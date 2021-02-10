#include "Shader/shader.hpp"

#include <vector>

#ifndef ARRAYSIZE
    #define ARRAYSIZE(arr) ((int)(sizeof(arr) / sizeof(arr[0])))
#endif

void Shader::InitProgram(const char* _vertStr, const char* _fragStr)
{
    GLuint prog = glCreateProgram();

    GLuint vertexShader = CreateShader(GL_VERTEX_SHADER,   1, &_vertStr);
    GLuint fragShader  = CreateShader(GL_FRAGMENT_SHADER, 1,  &_fragStr);

    glAttachShader(prog, vertexShader);
    glAttachShader(prog, fragShader);
    glLinkProgram(prog);

    GLint linkStatus;
    glGetProgramiv(prog, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        GLchar infoLog[1024];
        glGetProgramInfoLog(prog, ARRAYSIZE(infoLog), nullptr, infoLog);
        printf("Program link error: %s", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    program = prog;
}

GLuint Shader::CreateShader(GLenum _type, int _sourceCount, const char **_sources)
{
    GLuint shader = glCreateShader(_type);

    glShaderSource(shader, _sourceCount, _sources, nullptr);
    glCompileShader(shader);
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, ARRAYSIZE(infoLog), nullptr, infoLog);
        printf("Shader compilation error: %s", infoLog);
    }

    return shader;
}

void Shader::Activate()
{
    glUseProgram(program);
}
