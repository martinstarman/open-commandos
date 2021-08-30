#pragma once

#include <fstream>
#include <map>
#include <SDL.h>
#include <string>

namespace GreenBeret
{
    class WADFile
    {
    public:
        WADFile();
        WADFile(const std::string &path);
        ~WADFile();
        void Parse();
        SDL_Texture *WADFile::GetImage(const std::string &name);

    private:
        std::string path;
        std::ifstream file;
        std::map<std::string, SDL_Texture *> textures;
    };
} // namespace GreenBeret
