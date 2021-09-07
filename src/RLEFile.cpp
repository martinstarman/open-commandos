#include "RLEFile.h"
#include "Utils.h"
#include "Window.h"

#include <fstream>
#include <SDL.h>
#include <string>
#include <vector>

namespace GreenBeret
{
    RLEFile::RLEFile(const std::string &path)
        : h(0),
          w(0),
          pixels({}),
          paletteId(0)
    {
        file.open(path, std::ifstream::binary);
    }

    RLEFile::~RLEFile()
    {
        file.close();
    }

    int RLEFile::Parse(int offset)
    {
        std::vector<char> buffer;
        offset += 32; // skip name

        // number of pixels
        buffer.resize(8);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 8);
        int pixelNo = GetBufferValue(buffer);

        SDL_Log("RLE image pixels: %i", pixelNo);

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

        offset += 12;

        SDL_Log("RLE image size (WxH): %ix%i", w, h);

        // pixels
        pixels.resize(pixelNo);
        file.seekg(offset, file.beg);
        file.read(&pixels[0], pixelNo);

        offset += pixelNo;

        // line offset
        offset += 16 + (h * 4);

        // color palette
        buffer.resize(4);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 4);
        paletteId = GetBufferValue(buffer);

        SDL_Log("Palette id: %i", paletteId);

        return 64 + pixelNo + 16 + (h * 4) + 4;
    }

    SDL_Texture *RLEFile::GetImage(std::vector<char> palette)
    {
        std::vector<unsigned char> imagePixels;

        for (int i = 0; i < pixels.size(); i++)
        {
            if ((unsigned char)pixels.at(i) == 255) // transparent
            {
                i++;
                int compressedPixels = (unsigned char)pixels.at(i);

                for (int j = 0; j < compressedPixels; j++)
                {
                    imagePixels.push_back((unsigned char)255);
                    imagePixels.push_back((unsigned char)255);
                    imagePixels.push_back((unsigned char)255);
                    imagePixels.push_back(0);
                }
            }
            else if ((unsigned char)pixels.at(i) == 254) // semi transparent
            {
                i++;
                int compressedPixels = (unsigned char)pixels.at(i);

                for (int j = 0; j < compressedPixels; j++)
                {
                    i++;
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
                    imagePixels.push_back((unsigned char)127);
                }
            }
            else // opaque
            {
                int compressedPixels = (unsigned char)pixels.at(i);

                for (int j = 0; j < compressedPixels; j++)
                {
                    i++;
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

        // RGBA8888
        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(&imagePixels[0], w, h, 32, w * 4, rmask,
                                                        gmask, bmask, amask);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::Get()->renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }
} // namespace GreenBeret