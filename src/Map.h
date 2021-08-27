#pragma once
#include <string>
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
        int offset_x;
        int offset_y;

    private:
        Map();
        static Map *instance;
        WADFile *wad_file;
        VOLFile *vol_file;
        SECFile *sec_file;
        float sin40deg = 0.64278760968f;
    };
} // namespace GreenBeret
