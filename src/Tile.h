#pragma once

#include "Vector2.h"

#include <SDL.h>
#include <string>

namespace GreenBeret
{
    class Tile
    {
    public:
        Tile(float x, float y, float w, float h, float shiftX, float shiftY, int brightness,
             const std::string &fileName, const std::string &transformation);
        ~Tile();
        void CreateTexture(SDL_Texture *originalTexture);
        Vector2 position;
        Vector2 size;
        Vector2 shift;
        std::string fileName;
        std::string transformation;
        SDL_Texture *texture;

    private:
        int brightness;
    };
} // namespace GreenBeret
