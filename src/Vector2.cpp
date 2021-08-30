#include "Vector2.h"

#include <SDL.h>

namespace GreenBeret
{
    Vector2::Vector2(float x, float y)
        : x(x),
          y(y)
    {
    }

    Vector2::~Vector2() = default;

    Vector2 Vector2::operator+(const Vector2 p) const
    {
        return Vector2(x + p.x, y + p.y);
    }

    Vector2 Vector2::operator-(const Vector2 p) const
    {
        return Vector2(x - p.x, y - p.y);
    }

    Vector2::operator SDL_Point() const
    {
        return SDL_Point{(int)x, (int)y};
    }
} // namespace GreenBeret
