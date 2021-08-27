#pragma once
#include "Map.h"
#include "Window.h"

namespace GreenBeret
{
    class Game
    {
    public:
        Game();
        ~Game();
        void Run();
        void Render();
        void HandleKeyboardState();
        void HandleMouseState();
        int w;
        int h;
    };
} // namespace GreenBeret