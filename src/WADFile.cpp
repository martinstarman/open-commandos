#include "WADFile.h"
#include "BMPFile.h"
#include "RLEFile.h"
#include <fstream>
#include <SDL.h>
#include <string>
#include "Utils.h"
#include <vector>
#include "Window.h"

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
        int palettes_no = GetBufferValue(buffer);
        SDL_Log("Number of palettes: %i", palettes_no);

        offset += 4;

        // palettes
        std::vector<std::vector<char>> palettes;
        palettes.resize(palettes_no);
        buffer.resize(512);
        for (int i = 0; i < palettes_no; i++)
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
                BMPFile bmp_file(path);
                offset += bmp_file.Parse(offset);
                auto palette = palettes.at(bmp_file.palette_id);
                SDL_Texture *texture = bmp_file.GetImage(palette);
                textures[name] = texture;
            }
            else
            {
                RLEFile rle_file(path);
                offset += rle_file.Parse(offset);
                auto palette = palettes.at(rle_file.palette_id);
                SDL_Texture *texture = rle_file.GetImage(palette);
                textures[name] = texture;
            }
        }
    }

    SDL_Texture *WADFile::GetImage(const std::string &name)
    {
        return textures[name];
    }
} // namespace GreenBeret
