#pragma once

#include "Tile.h"
#include "Vector2.h"

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
        Vector2 center;
        int z;
        int h;
        std::vector<Vector2> points;
        std::vector<Tile> tiles;
    };
} // namespace GreenBeret
