#pragma once

#include "Vector2.h"

#include <string>

namespace GreenBeret
{
    class Tile
    {
    public:
        Tile(float x, float y, float w, float h, float offsetX, float offsetY, int brightness,
             const std::string &fileName, const std::string &transformation);
        ~Tile();
        Vector2 position;
        Vector2 size;
        std::string fileName;
        std::string transformation;

    private:
        Vector2 offset;
        int brightness;
    };
} // namespace GreenBeret
