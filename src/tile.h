#pragma once

#include <raylib.h>
#include <string>

#include "utils.h"

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
  void Load();
  void Render(int offsetX, int offsetY) const;

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
  std::string exportedSpriteName;
  bool isVisible;
  Texture texture;
  bool flipX;
  bool flipY;
};
