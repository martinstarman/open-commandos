#include "PointF.h"

#include <SDL.h>

namespace GreenBeret
{
    PointF::PointF(float x, float y)
        : x(x),
          y(y)
    {
    }

    PointF::PointF(int x, int y)
        : x((float)x),
          y((float)y)
    {
    }

    PointF::~PointF() = default;

    PointF PointF::operator+(const PointF p) const
    {
        return PointF(x + p.x, y + p.y);
    }

    PointF PointF::operator-(const PointF p) const
    {
        return PointF(x - p.x, y - p.y);
    }

    PointF::operator SDL_Point() const
    {
        return SDL_Point{(int)x, (int)y};
    }
} // namespace GreenBeret
