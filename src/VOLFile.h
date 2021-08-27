#pragma once
#include <fstream>
#include "Polygon.h"
#include <string>
#include "Tile.h"
#include <vector>

namespace GreenBeret
{
    class VOLFile
    {
    public:
        VOLFile();
        VOLFile(const std::string &path);
        ~VOLFile();
        void Parse();
        int w;
        int h;
        std::vector<Polygon> polygons;
        std::vector<Tile> tiles;

    private:
        std::ifstream file;
    };
} // namespace GreenBeret
