#include "mission.h"

Mission::Mission()
    : width(0),
      height(0),
      misFile(nullptr),
      volFile(nullptr),
      secFile(nullptr),
      wadFile(nullptr),
      offsetX(0),
      offsetY(0)
{
}

Mission::~Mission()
{
  delete misFile;
  delete secFile;
  delete volFile;
  delete wadFile;

  for (auto const &[_, texture] : textures)
  {
    UnloadTexture(*texture);
    delete texture;
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

  wadFile = new WadFile("DATOS/RECURSOS/BMPS/MAP/" + faseToken + ".WAD");
  textures = wadFile->Load();

  SortPolygons();
}

void Mission::Render() const
{
  for (auto *polygon : sortedPolygons)
  {
    for (const auto &tile : polygon->GetTiles())
    {
      if (tile.IsVisible())
      {
        Texture *texture = textures.at(tile.GetSpriteName());

        Rectangle src = {
            tile.IsFlippedX()
                ? (float)texture->width - (float)tile.GetWidth() - (float)tile.GetOffsetX()
                : (float)tile.GetOffsetX(),
            tile.IsFlippedY()
                ? (float)texture->height - (float)tile.GetHeight() - (float)tile.GetOffsetY()
                : (float)tile.GetOffsetY(),
            (float)tile.GetWidth() * (tile.IsFlippedX() ? -1 : 1),
            (float)tile.GetHeight() * (tile.IsFlippedY() ? -1 : 1)};

        Rectangle dest = {
            (float)tile.GetX() - offsetX,
            (float)tile.GetY() - offsetY,
            (float)tile.GetWidth(),
            (float)tile.GetHeight()};

        Vector2 origin = {0.0f, 0.0f};
        float rotation = 0;
        DrawTexturePro(*texture, src, dest, origin, rotation, WHITE);
      }
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
        Rectangle rectangle = {
            (float)tile.GetX() - offsetX,
            (float)tile.GetY() - offsetY,
            (float)tile.GetWidth(),
            (float)tile.GetHeight()};

        if (tile.IsVisible() && CheckCollisionPointRec(GetMousePosition(), rectangle))
        {
          std::string str = tile.GetSpriteName();
          str.append(" (")
              .append(std::to_string(tile.GetX()))
              .append(", ")
              .append(std::to_string(tile.GetY()))
              .append(")");
          DrawText(str.c_str(), GetMouseX() + 20, GetMouseY() + 10 + lines * 12, 10, YELLOW);
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

void Mission::SortPolygons()
{
  std::vector<Polygon> &polygons = volFile->GetRoot()->GetNode("MAPTABPOLYS")->GetListOfPolygons();
  sortedPolygons.reserve(polygons.size());

  for (auto &polygon : polygons)
  {
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
