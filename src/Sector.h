#pragma once

#include "PointF.h"

#include <vector>

namespace GreenBeret
{
    class Sector
    {
    public:
        Sector(std::vector<PointF> points);
        ~Sector();
        std::vector<PointF> points;

    private:
    };
} // namespace GreenBeret
