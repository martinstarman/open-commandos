#include "mission.h"

Mission::Mission()
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
}

void Mission::Render()
{
  for (const auto &polygon : volFile->GetPolygons())
  {
    for (const auto &tile : polygon.GetTiles())
    {
      std::string spriteName = tile.GetSpriteName();

      if (spriteName.at(0) != '-')
      {
        std::string textureName;

        if (spriteName.compare(spriteName.length() - 3, 3, "BMP") == 0)
        {
          textureName = Replace(spriteName, "BMP", "png");
        }
        else
        {
          textureName = Replace(spriteName, "RLE", "png");
        }

        if (textures.find(textureName) == textures.end())
        {
          Texture texture = LoadTexture(("export/" + textureName).c_str());
          textures.emplace(textureName, texture);
        }

        int x = (int)tile.GetX();
        int y = (int)tile.GetY();
        DrawTexture(textures.at(textureName), x, y, WHITE);
      }
    }
  }
}
