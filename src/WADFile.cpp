#include "WADFile.h"

#include "BMPFile.h"
#include "RLEFile.h"
#include "Utils.h"
#include "Window.h"

#include <fstream>
#include <SDL.h>
#include <string>
#include <vector>

namespace GreenBeret
{
    WADFile::WADFile() = default;

    WADFile::WADFile(const std::string &path)
        : path(path)
    {
        SDL_Log("Opening WAD file: %s", path.c_str());
        file.open(path, std::ifstream::binary);
    }

    WADFile::~WADFile()
    {
        file.close();
        for (const auto &texture : textures)
        {
            SDL_DestroyTexture(texture.second);
        }
    }

    void WADFile::Parse()
    {
        std::vector<char> buffer;
        int offset = 400; // skip wad file header

        // file size
        file.seekg(0, file.end);
        int size = (int)file.tellg();

        // number of palettes
        buffer.resize(4);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 4);
        int paletteNo = GetBufferValue(buffer);
        SDL_Log("Number of palettes: %i", paletteNo);

        offset += 4;

        // palettes
        std::vector<std::vector<char>> palettes;
        palettes.resize(paletteNo);
        buffer.resize(512);
        for (int i = 0; i < paletteNo; i++)
        {
            file.seekg(offset, file.beg);
            file.read(&buffer[0], 512);
            palettes.at(i) = buffer;
            offset += 525;
        }

        // number of images
        buffer.resize(4);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 4);
        int images = GetBufferValue(buffer);

        SDL_Log("Number of images: %i", images);

        offset += 4;

        // images
        buffer.resize(32); // image file name
        int i = 1;

        while (offset < size)
        {
            file.seekg(offset, file.beg);
            file.read(&buffer[0], 32);

            std::string name(buffer.begin(), buffer.end());
            name.erase(std::find(name.begin(), name.end(), '\0'), name.end());
            SDL_Log("Loading image no. %i: %s", i, name.c_str());
            i++;

            if (name.compare(name.length() - 3, 3, "BMP") == 0)
            {
                BMPFile bmpFile(path);
                offset += bmpFile.Parse(offset);
                auto palette = palettes.at(bmpFile.paletteId);
                SDL_Texture *texture = bmpFile.GetImage(palette);
                textures[name] = texture;
            }
            else
            {
                RLEFile rleFile(path);
                offset += rleFile.Parse(offset);
                auto palette = palettes.at(rleFile.paletteId);
                SDL_Texture *texture = rleFile.GetImage(palette);
                textures[name] = texture;
            }
        }
    }

    SDL_Texture *WADFile::GetImage(const std::string &name)
    {
        return textures[name];
    }
} // namespace GreenBeret
