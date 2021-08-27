#pragma once
#include "PointF.h"
#include <string>
#include <vector>

namespace GreenBeret
{
    class Polygon
    {
    public:
        Polygon(const std::string &name, float x, float y, int z, int h, int vertices_no, int tiles_no);
        ~Polygon();
        std::string name;
        PointF center;
        int z;
        int h;
        int vertices_no;
        int tiles_no;
        std::vector<PointF> points;
    };
} // namespace GreenBeret
