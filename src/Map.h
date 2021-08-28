#pragma once
#include <string>
#include "PointF.h"
#include "SECFile.h"
#include "VOLFile.h"
#include "WADFile.h"

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
        WADFile *wad_file;
        VOLFile *vol_file;
        SECFile *sec_file;
    };
} // namespace GreenBeret
