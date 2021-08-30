#pragma once

#include <SDL.h>

namespace GreenBeret
{
    class Vector2
    {
    public:
        Vector2(float x, float y);
        ~Vector2();
        float x;
        float y;
        Vector2 operator+(const Vector2 p) const;
        Vector2 operator-(const Vector2 p) const;
        operator SDL_Point() const;
    };
} // namespace GreenBeret
