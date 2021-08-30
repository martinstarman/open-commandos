#pragma once

#include "PointF.h"
#include "SECFile.h"
#include "VOLFile.h"
#include "WADFile.h"

#include <string>

namespace GreenBeret
{
    class Map
    {
    public:
        static Map *Get();
        ~Map();
        void Load(const std::string &name);
        void Render();
        void Move(int x, int y);
        PointF offset;
    private:
        Map();
        static Map *instance;
        WADFile *wadFile;
        VOLFile *volFile;
        SECFile *secFile;
    };
} // namespace GreenBeret
