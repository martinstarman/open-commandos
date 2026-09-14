#include "mission.h"

Mission::Mission()
    : width(0),
      height(0),
      misFile(nullptr),
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

  if (offsetX < 0)
  {
    offsetX = 0;
  }

  // TODO: remove constants
  if (offsetX > width - 800)
  {
    offsetX = width - 800;
  }

  if (offsetY < 0)
  {
    offsetY = 0;
  }

  // TODO: remove constants
  if (offsetY > height - 600)
  {
    offsetY = height - 600;
  }
}

void Mission::Load(const std::string &name, const std::string &faseToken)
{
  misFile = new MisFile("DATOS/MISIONES/" + name);
  misFile->Parse();

  std::string volFileName = misFile->GetRoot()
                                ->GetNode("." + faseToken)
                                ->GetNode(".DATOSFICHEROSMISION")
                                ->GetNode(".VOLUMENES")
                                ->GetString();

  volFile = new VolFile("DATOS/MISIONES/" + volFileName);
  volFile->Parse();

  std::vector<double> mapDimensions = volFile->GetRoot()
                                          ->GetNode("MAPDIMXY")
                                          ->GetListOfNumbers();

  width = mapDimensions.at(0);
  height = mapDimensions.at(1);

  std::string secFileName = misFile->GetRoot()
                                ->GetNode("." + faseToken)
                                ->GetNode(".DATOSFICHEROSMISION")
                                ->GetNode(".SECTORES")
                                ->GetString();

  secFile = new SecFile("DATOS/MISIONES/" + secFileName);
  secFile->Parse();

  LoadTiles();
}

void Mission::Render() const
{
  for (auto *polygon : sortedPolygons)
  {
    for (const auto &tile : polygon->GetTiles())
    {
      tile.Render(offsetX, offsetY);
    }
  }
  if (g_debug)
  {
    RenderDebug();
  }
}

void Mission::RenderDebug() const
{
  // tile sprite name
  {
    int lines = 0;

    for (auto *polygon : sortedPolygons)
    {
      for (const auto &tile : polygon->GetTiles())
      {
        if (tile.IsVisible() && CheckCollisionPointRec(GetMousePosition(), tile.GetRect(offsetX, offsetY)))
        {
          DrawText(tile.GetSpriteName().c_str(), GetMouseX() + 10, GetMouseY() + 10 + lines * 12, 10, YELLOW);
          lines++;
        }
      }
    }
  }

  // polygons
  {
    for (auto *polygon : sortedPolygons)
    {
      std::vector<std::tuple<double, double>> vertices = polygon->GetVertices();
      double centerX = polygon->GetCenterX();
      double centerY = polygon->GetCenterY();

      for (size_t i = 0; i < vertices.size(); ++i)
      {
        auto [x1, y1] = vertices.at(i);
        auto [x2, y2] = vertices.at((i + 1) % vertices.size());

        DrawLine(
            (int)(centerX + x1) - offsetX,
            (int)((centerY + y1) * g_sin40) - offsetY,
            (int)(centerX + x2) - offsetX,
            (int)((centerY + y2) * g_sin40) - offsetY,
            YELLOW);
      }
    }
  }
}

void Mission::LoadTiles()
{
  std::vector<Polygon> &polygons = volFile->GetRoot()->GetNode("MAPTABPOLYS")->GetListOfPolygons();

  sortedPolygons.reserve(polygons.size());

  for (auto &polygon : polygons)
  {
    for (auto &tile : polygon.GetTiles())
    {
      tile.Load();
    }

    sortedPolygons.push_back(&polygon);
  }

  std::sort(sortedPolygons.begin(), sortedPolygons.end(), [](const Polygon *a, const Polygon *b) -> bool
            { return a->GetCenterZ() < b->GetCenterZ(); });
}

int Mission::GetWidth() const
{
  return width;
}

int Mission::GetHeight() const
{
  return height;
}
