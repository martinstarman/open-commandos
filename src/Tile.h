#pragma once

#include "PointF.h"

#include <string>

namespace GreenBeret
{
    class Tile
    {
    public:
        Tile(int x, int y, int w, int h, int offsetX, int offsetY, int brightness,
             const std::string &fileName, const std::string &transformation);
        ~Tile();
        PointF position;
        int w;
        int h;
        std::string fileName;
        std::string transformation;

    private:
        PointF offset;
        int brightness;
    };
} // namespace GreenBeret
