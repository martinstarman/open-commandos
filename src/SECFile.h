#pragma once

#include "PointF.h"
#include "Sector.h"

#include <fstream>
#include <string>
#include <vector>

namespace GreenBeret
{
    enum class BLOCK
    {
        VERTEX = 0,
        SECTOR = 1,
        BRIDGE = 2,
        AREA = 3,
        CONNECTION = 4,
    };

    class SECFile
    {
    public:
        SECFile(const std::string &path);
        ~SECFile();
        void Parse();
        std::vector<Sector> sectors;

    private:
        std::ifstream file;
        BLOCK block;
        std::vector<PointF> points;
        // TODO: same variable is in VOLFile.h
        // the player looks down at the map from an angle of 40 degrees. That means that the
        // y-coordinates have to be multiplied by sin(40)
        float sin40 = 0.64278760968f;
    };
} // namespace GreenBeret
