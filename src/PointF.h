#pragma once

#include <SDL.h>

namespace GreenBeret
{
    class PointF
    {
    public:
        PointF(float x, float y);
        PointF(int x, int y);
        ~PointF();
        float x;
        float y;
        PointF operator+(const PointF p) const;
        PointF operator-(const PointF p) const;
        operator SDL_Point() const;
    };
} // namespace GreenBeret
