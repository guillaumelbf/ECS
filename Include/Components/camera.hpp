#pragma once

#include <cmath>

#include "Maths/extendedTypes.hpp"

struct Camera
{
    Mat4 projection;

    static Mat4 MakeProjectionTransform(float fov, float near, float far, unsigned int viewWidth, unsigned int viewHeight)
    {
        float aspect = (float)viewWidth / (float)viewHeight;
        float zoom = 1.f / tanf(fov / 2.f);

        Mat4 transform(0);
        transform.e[0]  = zoom / aspect;
        transform.e[5]  = zoom;
        transform.e[10] = -((far + near) / (far - near));
        transform.e[11] = -1;
        transform.e[14] = -((2.f * far * near) / (far - near));

        return transform;
    }
};
