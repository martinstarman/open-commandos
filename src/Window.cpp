#include "Window.h"

#include <SDL.h>

namespace GreenBeret
{
    Window *Window::instance = nullptr;

    Window *Window::Get()
    {
        if (instance == nullptr)
        {
            instance = new Window();
        }
        return instance;
    }

    Window::Window()
        : w(640),
          h(480)
    {

        window = SDL_CreateWindow("Green Beret", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  w, h, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }

    Window::~Window()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        delete instance;
    }
} // namespace GreenBeret