#include "Sector.h"
#include "PointF.h"
#include <vector>

namespace GreenBeret
{
    Sector::Sector(std::vector<PointF> points)
        : points(points)
    {
    }

    Sector::~Sector() = default;
} // namespace GreenBeret
