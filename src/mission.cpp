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

  LoadTiles();
}

void Mission::Render()
{
  for (auto &polygon : volFile->GetPolygons())
  {
    for (const auto &tile : polygon.GetTiles())
    {
      tile.Render(offsetX, offsetY);
    }
  }
}

void Mission::LoadTiles()
{
  for (auto &polygon : volFile->GetPolygons())
  {
    for (auto &tile : polygon.GetTiles())
    {
      tile.Load();
    }
  }
}
