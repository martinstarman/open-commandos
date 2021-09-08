#include "Game.h"

#include "DIRFile.h"
#include "Map.h"
#include "Utils.h"
#include "Window.h"

#include <filesystem>

namespace GreenBeret
{
    Game::Game()
        : w(800),
          h(600)
    {
        if (!std::filesystem::exists("DATOS"))
        {
            // TODO: why is there no /DATOS/RECURSOS/BMPS/MAP directory in steam versions??
            // TODO: check if file exists
            DIRFile dirFile("WARGAME.DIR");
            dirFile.Extract();
        }

        Map::Get()->Load("0000");
    }

    Game::~Game() = default;

    void Game::Run()
    {
        bool isRunning = true;
        SDL_Event event;

        while (isRunning)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    isRunning = false;
                }
            }

            HandleKeyboardState();
            // HandleMouseState();
            Render();
        }
    }

    void Game::Render()
    {
        SDL_SetRenderDrawColor(Window::Get()->renderer, 0, 0, 0, 255);
        SDL_RenderClear(Window::Get()->renderer);
        Map::Get()->Render();
        SDL_RenderPresent(Window::Get()->renderer);
    }

    void Game::HandleKeyboardState()
    {
        SDL_PumpEvents();
        const uint8_t *state = SDL_GetKeyboardState(NULL);
        int x = 0;
        int y = 0;

        if (state[SDL_SCANCODE_LEFT])
        {
            x -= 5;
        }
        if (state[SDL_SCANCODE_RIGHT])
        {
            x += 5;
        }
        if (state[SDL_SCANCODE_UP])
        {
            y -= 5;
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            y += 5;
        }

        Map::Get()->Move(x, y);
    }

    void Game::HandleMouseState()
    {
        SDL_PumpEvents();
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);
        SDL_Log("Mouse pos: %f, %f", x + Map::Get()->offset.x, y + Map::Get()->offset.y);
    }
} // namespace GreenBeret
