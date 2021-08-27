#include "RLEFile.h"
#include <fstream>
#include <SDL.h>
#include <string>
#include "Utils.h"
#include <vector>
#include "Window.h"

namespace GreenBeret
{
    RLEFile::RLEFile(const std::string &path)
        : pixels_no(0),
          h(0),
          w(0),
          pixels({}),
          palette_id(0)
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
        pixels_no = GetBufferValue(buffer);

        SDL_Log("RLE image pixels: %i", pixels_no);

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
        pixels.resize(pixels_no);
        file.seekg(offset, file.beg);
        file.read(&pixels[0], pixels_no);

        offset += pixels_no;

        // line offset
        offset += 16 + (h * 4);

        // color palette
        buffer.resize(4);
        file.seekg(offset, file.beg);
        file.read(&buffer[0], 4);
        palette_id = GetBufferValue(buffer);

        SDL_Log("Palette id: %i", palette_id);

        return 64 + pixels_no + 16 + (h * 4) + 4;
    }

    SDL_Texture *RLEFile::GetImage(std::vector<char> palette)
    {
        std::vector<char> image_pixels;

        for (int i = 0; i < pixels.size(); i++)
        {
            if ((unsigned char)pixels.at(i) == 255) // transparent
            {
                i++;
                int compressed_pixels = (unsigned char)pixels.at(i);

                for (int j = 0; j < compressed_pixels; j++)
                {
                    // pink color
                    image_pixels.push_back(28);
                    image_pixels.push_back((char)248);
                }
            }
            else if ((unsigned char)pixels.at(i) == 254) // semi transparent
            {
                i++;
                int compressed_pixels = (unsigned char)pixels.at(i);

                for (int j = 0; j < compressed_pixels; j++)
                {
                    i++;
                    int palette_index = (unsigned char)pixels.at(i);
                    int color1 = palette.at(palette_index * 2);
                    int color2 = palette.at(palette_index * 2 + 1); // TODO: semi transparent
                    image_pixels.push_back(color1);
                    image_pixels.push_back(color2); // TODO: 127
                }
            }
            else // opaque
            {
                int compressed_pixels = (unsigned char)pixels.at(i);

                for (int j = 0; j < compressed_pixels; j++)
                {
                    i++;
                    int palette_index = (unsigned char)pixels.at(i);
                    int color1 = palette.at(palette_index * 2);
                    int color2 = palette.at(palette_index * 2 + 1);
                    image_pixels.push_back(color1);
                    image_pixels.push_back(color2);
                }
            }
        }

        // RGB 565
        // TODO: https://wiki.libsdl.org/SDL_SetSurfaceRLE ??
        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(&image_pixels[0], w, h, 16, w * 2, 0xF800,
                                                        0x07E0, 0x001F, 0x0000);
        Uint32 colorkey = SDL_MapRGB(surface->format, 255, 0, 225);
        SDL_SetColorKey(surface, SDL_TRUE, colorkey);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::Get()->renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }
} // namespace GreenBeret