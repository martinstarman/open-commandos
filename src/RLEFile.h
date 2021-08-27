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
        int palette_id;

    private:
        std::ifstream file;
        int pixels_no;
        int h;
        int w;
        std::vector<char> pixels;
    };

}