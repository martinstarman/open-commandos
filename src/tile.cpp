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
      transformation(transformation),
      texture({})
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

Tile::~Tile()
{
  if (IsTextureValid(texture))
  {
    UnloadTexture(texture);
  }
}

void Tile::Load()
{
  if (isVisible)
  {
    texture = LoadTexture(("export/" + exportedSpriteName).c_str()); // TODO: load dir
  }
}

void Tile::Render(int offsetX, int offsetY) const
{
  if (isVisible)
  {
    int renderX = (int)x - offsetX;
    int renderY = (int)y - offsetY;
    DrawTexture(texture, renderX, renderY, WHITE);
  }
}
