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
  isVisible = spriteName.at(0) != '-';
  isFlippedX = transformation.at(0) == 'X';
  isFlippedY = transformation.at(1) == 'Y';
}

Tile::~Tile() = default;

const std::string &Tile::GetSpriteName() const
{
  return spriteName;
}

const bool Tile::IsVisible() const
{
  return isVisible;
}

const bool Tile::IsFlippedX() const
{
  return isFlippedX;
}

const bool Tile::IsFlippedY() const
{
  return isFlippedY;
}

const double Tile::GetX() const
{
  return x;
}

const double Tile::GetY() const
{
  return y;
}

const double Tile::GetWidth() const
{
  return width;
}

const double Tile::GetHeight() const
{
  return height;
}

const double Tile::GetOffsetX() const
{
  return offsetX;
}

const double Tile::GetOffsetY() const
{
  return offsetY;
}
