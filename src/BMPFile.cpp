#include "BMPFile.h"
#include <fstream>
#include <SDL.h>
#include <string>
#include "Utils.h"
#include <vector>
#include "Window.h"

#include <iostream>

namespace GreenBeret
{
    BMPFile::BMPFile(const std::string &path)
        : pixels_no(0),
          h(0),
          w(0),
          pixels({}),
          palette_id(0)
    {
        file.open(path, std::ifstream::binary);
    }

    BMPFile::~BMPFile()
    {
        file.close();
    }

    int BMPFile::Parse(int offset)
    {
        std::vector<char> buffer;
        offset += 32; // skip name

        // number of pixels
        buffer.resize(8);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 8);
        pixels_no = GetBufferValue(buffer);

        SDL_Log("BMP image pixels: %i", pixels_no);

        offset += 16;

        // height
        buffer.resize(4);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 4);
        h = GetBufferValue(buffer);

        offset += 4;

        // width
        buffer.resize(4);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 4);
        w = GetBufferValue(buffer);

        SDL_Log("BMP image size (WxH): %ix%i", w, h);

        offset += 12;

        // pixels
        pixels.resize(pixels_no);
        file.seekg(offset, file.beg);
        file.read(&pixels[0], pixels_no);

        // color palette id
        offset += (int)pixels.size();
        buffer.resize(4);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 4);
        palette_id = GetBufferValue(buffer);

        SDL_Log("Palette id: %i", palette_id);

        return 64 + pixels_no + 4; // header size + pixels + palette id
    }

    SDL_Texture *BMPFile::GetImage(std::vector<char> palette)
    {
        std::vector<char> image_pixels;

        // skip last byte
        for (int i = 0; i < pixels.size() - 1; i++)
        {
            // skip last 2 bytes (are same as 2 first bytes)
            if (i % (w + 2) != w && i % (w + 2) != w + 1)
            {
                int palette_index = (unsigned char)pixels.at(i);
                int color1 = palette.at(palette_index * 2);
                int color2 = palette.at(palette_index * 2 + 1);
                image_pixels.push_back(color1);
                image_pixels.push_back(color2);
            }
        }

        // RGB 565
        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(&image_pixels[0], w, h, 16, w * 2, 0xF800,
                                                        0x07E0, 0x001F, 0x0000);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::Get()->renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }
} // namespace GreenBeret