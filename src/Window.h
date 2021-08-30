#pragma once

#include "Vector2.h"

#include <SDL.h>

namespace GreenBeret
{
    class Window
    {
    public:
        static Window *Get();
        ~Window();
        Vector2 size;
        SDL_Renderer *renderer;

    private:
        Window();
        static Window *instance;
        SDL_Window *window;
    };
} // namespace GreenBeret
