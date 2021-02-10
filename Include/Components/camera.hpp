#pragma once

#include <cmath>

#include "Maths/extendedTypes.hpp"

#define M_PI 3.14159265358979323846

struct Camera
{
    Mat4 projection;

    static Mat4 MakeProjectionTransform(float fov, float near, float far, unsigned int viewWidth, unsigned int viewHeight)
    {
        float zClipBias0 =
                (far + near)
                / (far - near);

        float zClipBias1 =
                (2.0f * far * near)
                / (far - near);

        float zoomX = 1.0f / tanf((fov / 2.0f) * (M_PI / 180.0f));
        float zoomY = (zoomX * static_cast<float>(viewWidth)) / static_cast<float>(viewHeight);

        Mat4 transform;
        transform.e[0]  = zoomX;
        transform.e[5]  = zoomY;
        transform.e[10] = -zClipBias0;
        transform.e[11] = -1;
        transform.e[14] = -zClipBias1;

        return transform;
    }
};
