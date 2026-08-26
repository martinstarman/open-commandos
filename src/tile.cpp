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
  if (spriteName.at(0) == '-')
  {
    isVisible = false;
    exportedSpriteName = spriteName.substr(1);
  }
  else
  {
    isVisible = true;
    exportedSpriteName = spriteName.substr(0);
  }

  exportedSpriteName = Replace(exportedSpriteName, "BMP", "png");
  exportedSpriteName = Replace(exportedSpriteName, "RLE", "png");
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

std::string Tile::GetExportedSpriteName() const
{
  return exportedSpriteName;
}

bool Tile::IsVisible() const
{
  return isVisible;
}
