#include "Sector.h"

#include "Vector2.h"

#include <vector>

namespace GreenBeret
{
    Sector::Sector(std::vector<Vector2> points)
        : points(points)
    {
    }

    Sector::~Sector() = default;
} // namespace GreenBeret
