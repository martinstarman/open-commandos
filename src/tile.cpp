#include "tile.h"

Tile::Tile(
    double x,
    double y,
    double width,
    double height,
    double offsetX,
    double offsetY,
    double brightness,
    const std::string &spriteName,
    const std::string &transformation)
    : x(x),
      y(y),
      width(width),
      height(height),
      offsetX(offsetX),
      offsetY(offsetY),
      brightness(brightness),
      spriteName(spriteName),
      transformation(transformation)
{
}

Tile::~Tile() = default;

double Tile::GetX() const
{
  return x;
}

double Tile::GetY() const
{
  return y;
}

std::string Tile::GetSpriteName() const
{
  return spriteName;
}
