#pragma once

struct Int2
{
    int x; int y;
};

struct Int3
{
    int x; int y; int z;
};

struct Int4
{
    int x; int y; int z; int w;
};

struct Float2
{
    float x; float y;
};

struct Float3
{
    float x; float y; float z;
};

struct Float4
{
    float x; float y; float z; float w;
};

struct Mat4
{
    float e[16] {};

    Mat4()
    {
        e[0] = 1;
        e[5] = 1;
        e[10]= 1;
        e[15]= 1;
    }

    Mat4(float _f)
    {
        for(size_t i = 0 ; i < 16 ; i++)
            e[i] = _f;
    }

    float at(const size_t _row, const size_t _col) const
    {
        return e[4 * _col + _row];
    }

    Mat4 operator*(const Mat4& _mat)
    {
        Mat4 result(0);

        for (int i = 0; i < 16; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result.e[i] += at(i % 4, j) * _mat.at(j,(int)i / 4);
            }
        }

        return result;
    }

    /*Float4 operator*(Float4 const& _vec)
    {
        return Vec4(
                (rhs.x * m[0][0]) + (rhs.y * m[0][1]) + (rhs.z * m[0][2]) + (rhs.w * m[0][3]),
                (rhs.x * m[1][0]) + (rhs.y * m[1][1]) + (rhs.z * m[1][2]) + (rhs.w * m[1][3]),
                (rhs.x * m[2][0]) + (rhs.y * m[2][1]) + (rhs.z * m[2][2]) + (rhs.w * m[2][3]),
                (rhs.x * m[3][0]) + (rhs.y * m[3][1]) + (rhs.z * m[3][2]) + (rhs.w * m[3][3]));
    }*/
};



