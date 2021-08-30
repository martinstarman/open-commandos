#pragma once

#include <fstream>
#include <SDL.h>
#include <string>
#include <vector>

namespace GreenBeret
{
    class RLEFile
    {
    public:
        RLEFile(const std::string &path);
        ~RLEFile();
        int Parse(int offset);
        SDL_Texture *GetImage(std::vector<char> palette);
        int paletteId;

    private:
        std::ifstream file;
        int h;
        int w;
        std::vector<char> pixels;
    };

}