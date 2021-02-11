#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>

#include "Maths/extendedTypes.hpp"

class Shader
{
private:
    GLuint program;

    GLuint CreateShader(GLenum _type, int _sourceCount, const char** _sources);
public:

    void InitProgram(const char* _vertStr, const char* _fragStr);

    template<typename T>
    void SetUniform(const std::string& name, const T& value)
    {
        if constexpr (std::is_same_v<T, Mat4>)
        {
            glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, (GLfloat*)value.e);
        }
        else if constexpr (std::is_same_v<T, Float3>)
        {
            glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, (GLfloat*)&value);
        }
    }

    void Activate();
};

