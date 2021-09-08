#pragma once

#include "Polygon.h"
#include "Tile.h"

#include <fstream>
#include <string>
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
        std::vector<Polygon *> polygons;

    private:
        std::ifstream file;
        // TODO: same variable is in SECFile.h
        // the player looks down at the map from an angle of 40 degrees. That means that the
        // y-coordinates have to be multiplied by sin(40)
        float sin40 = 0.64278760968f;
    };
} // namespace GreenBeret
