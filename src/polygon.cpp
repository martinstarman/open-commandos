#include "polygon.h"

Polygon::Polygon(
    const std::string &name,
    double centerX,
    double centerY,
    double centerZ,
    double height,
    double numberOfVertices,
    double numberOfTiles)
    : name(name),
      centerX(centerX),
      centerY(centerY),
      centerZ(centerZ),
      height(height),
      numberOfVertices(numberOfVertices),
      numberOfTiles(numberOfTiles)
{
}

Polygon::~Polygon() = default;

void Polygon::AddPoint(double x, double y)
{
  vertices.push_back(std::make_tuple(x, y));
}

std::vector<std::tuple<double, double>> Polygon::GetVertices() const
{
  assert(numberOfVertices == vertices.size());
  return vertices;
}

void Polygon::AddTile(Tile tile)
{
  tiles.push_back(tile);
}

std::vector<Tile> Polygon::GetTiles() const
{
  assert(numberOfTiles == tiles.size());
  return tiles;
}
