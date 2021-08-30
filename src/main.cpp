#include "Game.h"

#include <SDL.h>

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    GreenBeret::Game *game = new GreenBeret::Game();
    game->Run();

    delete game;
    SDL_Quit();
    return 0;
}