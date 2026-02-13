#pragma once

#include <string>

class Tile
{
public:
  Tile(
      double x,
      double y,
      double width,
      double height,
      double offsetX,
      double offsetY,
      double brightness,
      const std::string &spriteName,
      const std::string &transformation);
  ~Tile();

private:
  double x;
  double y;
  double width;
  double height;
  double offsetX;
  double offsetY;
  double brightness;
  std::string spriteName;
  std::string transformation;
};
