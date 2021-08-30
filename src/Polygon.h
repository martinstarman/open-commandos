#pragma once

#include "PointF.h"
#include "Tile.h"

#include <string>
#include <vector>

namespace GreenBeret
{
    class Polygon
    {
    public:
        Polygon(const std::string &name, float x, float y, int z, int h);
        ~Polygon();
        std::string name;
        PointF center;
        int z;
        int h;
        std::vector<PointF> points;
        std::vector<Tile> tiles;
    };
} // namespace GreenBeret
