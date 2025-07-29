#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "utils/dir_file.h"

int main()
{
  const int windowWidth = 800;
  const int windowHeight = 600;
  const int buttonWidth = 200;
  const int buttonHeight = 32;

  InitWindow(windowWidth, windowHeight, "openCommandos");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Hello openCommandos!", 20, 20, 20, BLACK);

    if (GuiButton(
            (Rectangle){
                windowWidth / 2 - buttonWidth / 2,
                windowHeight / 2 - buttonHeight / 2,
                buttonWidth,
                buttonHeight},
            "#7#Extract DIR file"))
    {
      DirFile dirFile = DirFile();
      dirFile.Extract();
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
