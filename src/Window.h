#pragma once
#include <SDL.h>

namespace GreenBeret
{
    class Window
    {
    public:
        static Window *Get();
        ~Window();
        int w;
        int h;
        SDL_Renderer *renderer;

    private:
        Window();
        static Window *instance;
        SDL_Window *window;
    };
} // namespace GreenBeret
