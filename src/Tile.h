#pragma once
#include <string>

namespace GreenBeret
{
    class Tile
    {
    public:
        Tile(int x, int y, int w, int h, int offset_x, int offset_y, int brightness,
             const std::string &sprite, const std::string &transformation);
        ~Tile();
        int x;
        int y;
        int w;
        int h;
        std::string sprite;
        std::string transformation;

    private:
        int offset_x;
        int offset_y;
        int brightness;
    };
} // namespace GreenBeret
