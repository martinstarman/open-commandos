#pragma once

#include "Vector2.h"

#include <vector>

namespace GreenBeret
{
    class Sector
    {
    public:
        Sector(std::vector<Vector2> points);
        ~Sector();
        std::vector<Vector2> points;

    private:
    };
} // namespace GreenBeret
