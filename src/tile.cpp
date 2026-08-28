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

  flipX = transformation.at(0) == 'X';
  flipY = transformation.at(1) == 'Y';
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
    SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
  }
}

void Tile::Render(int cameraOffsetX, int cameraOffsetY) const
{
  if (isVisible)
  {
    Rectangle src = {
        (float)-offsetX,
        (float)-offsetY,
        (float)width * (flipX ? -1 : 1),
        (float)height * (flipY ? -1 : 1)};

    Rectangle dest = {
        (float)x - cameraOffsetX,
        (float)y - cameraOffsetY,
        (float)width,
        (float)height};

    Vector2 origin = {0.0f, 0.0f};

    float rotation = 0;

    DrawTexturePro(texture, src, dest, origin, rotation, WHITE);
  }
}
