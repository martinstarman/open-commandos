#pragma once

#include <cassert>
#include <string>
#include <tuple>
#include <vector>

#include "tile.h"

class Polygon
{
public:
  Polygon(
      const std::string &name,
      double centerX,
      double centerY,
      double centerZ,
      double height,
      double numberOfVertices,
      double numberOfTiles);
  ~Polygon();
  void AddPoint(double x, double y);
  std::vector<std::tuple<double, double>> GetVertices();
  void AddTile(Tile tile);
  std::vector<Tile> GetTiles();

private:
  std::string name;
  double centerX;
  double centerY;
  double centerZ;
  double height;
  double numberOfVertices;
  double numberOfTiles;
  std::vector<std::tuple<double, double>> vertices;
  std::vector<Tile> tiles;
};
