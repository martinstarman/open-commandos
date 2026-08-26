#include "mission.h"

Mission::Mission()
    : misFile(nullptr),
      volFile(nullptr),
      secFile(nullptr),
      offsetX(0),
      offsetY(0)
{
}

Mission::~Mission()
{
  delete misFile;
  delete secFile;
  delete volFile;

  for (auto const [_, texture] : textures)
  {
    UnloadTexture(texture);
  }
}

void Mission::Update()
{
  if (IsKeyDown(KEY_LEFT))
  {
    offsetX = offsetX - 5;
  }

  if (IsKeyDown(KEY_RIGHT))
  {
    offsetX = offsetX + 5;
  }

  if (IsKeyDown(KEY_UP))
  {
    offsetY = offsetY - 5;
  }

  if (IsKeyDown(KEY_DOWN))
  {
    offsetY = offsetY + 5;
  }
}

void Mission::Load(const std::string &name)
{
  misFile = new MisFile("DATOS/MISIONES/MAPA" + name + ".MIS");
  misFile->Parse();

  std::string volFileName = misFile->GetRoot()
                                ->GetNode(".FASE" + name)
                                ->GetNode(".DATOSFICHEROSMISION")
                                ->GetNode(".VOLUMENES")
                                ->GetString();

  volFile = new VolFile("DATOS/MISIONES/" + volFileName);
  volFile->Parse();

  std::string secFileName = misFile->GetRoot()
                                ->GetNode(".FASE" + name)
                                ->GetNode(".DATOSFICHEROSMISION")
                                ->GetNode(".SECTORES")
                                ->GetString();

  secFile = new SecFile("DATOS/MISIONES/" + secFileName);
  secFile->Parse();

  LoadTextures();
}

void Mission::Render()
{
  for (const auto &polygon : volFile->GetPolygons())
  {
    for (const auto &tile : polygon.GetTiles())
    {
      if (tile.IsVisible())
      {
        int x = (int)tile.GetX() - offsetX;
        int y = (int)tile.GetY() - offsetY;
        DrawTexture(textures.at(tile.GetExportedSpriteName()), x, y, WHITE);
      }
    }
  }
}

void Mission::LoadTextures()
{
  for (const auto &polygon : volFile->GetPolygons())
  {
    for (const auto &tile : polygon.GetTiles())
    {

      if (tile.IsVisible())
      {
        std::string exportedSpriteName = tile.GetExportedSpriteName();
        Texture texture = LoadTexture(("export/" + exportedSpriteName).c_str()); // TODO: load dir
        textures.emplace(exportedSpriteName, texture);
      }
    }
  }
}
