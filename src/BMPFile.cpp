#include "BMPFile.h"

#include "Utils.h"
#include "Window.h"

#include <fstream>
#include <SDL.h>
#include <string>
#include <vector>
#include <iostream>

namespace GreenBeret
{
    BMPFile::BMPFile(const std::string &path)
        : h(0),
          w(0),
          pixels({}),
          paletteId(0)
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
        int pixelNo = GetBufferValue(buffer);

        SDL_Log("BMP image pixels: %i", pixelNo);

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
        pixels.resize(pixelNo);
        file.seekg(offset, file.beg);
        file.read(&pixels[0], pixelNo);

        // color palette id
        offset += (int)pixels.size();
        buffer.resize(4);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 4);
        paletteId = GetBufferValue(buffer);

        SDL_Log("Palette id: %i", paletteId);

        return 64 + pixelNo + 4; // header size + pixels + palette id
    }

    SDL_Texture *BMPFile::GetImage(std::vector<char> palette)
    {
        std::vector<char> imagePixels;

        // skip last byte
        for (int i = 0; i < pixels.size() - 1; i++)
        {
            // skip last 2 bytes (are same as 2 first bytes)
            if (i % (w + 2) != w && i % (w + 2) != w + 1)
            {
                int paletteIndex = (unsigned char)pixels.at(i);
                // GGGBBBBB
                unsigned char firstByte = palette.at(paletteIndex * 2);
                // RRRRRGGG
                unsigned char secondByte = palette.at(paletteIndex * 2 + 1);
                // RRRRRGGGGGGBBBBB
                unsigned int color = (int)secondByte << 8 | firstByte;
                // RRRRR000
                unsigned int r = (color & 0xF800) >> 8;
                // GGGGGG00
                unsigned int g = (color & 0x07E0) >> 3;
                // BBBBB000
                unsigned int b = (color & 0x001F) << 3;

                imagePixels.push_back((unsigned char)r);
                imagePixels.push_back((unsigned char)g);
                imagePixels.push_back((unsigned char)b);
                imagePixels.push_back((unsigned char)255);
            }
        }

        Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif

        // RGB8888
        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(&imagePixels[0], w, h, 32, w * 4, rmask,
                                                        gmask, bmask, amask);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::Get()->renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }
} // namespace GreenBeret