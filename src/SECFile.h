#pragma once
#include <fstream>
#include "PointF.h"
#include "Sector.h"
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
    };
} // namespace GreenBeret
