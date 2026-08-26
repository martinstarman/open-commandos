#pragma once

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
  double GetX() const;
  double GetY() const;
  std::string GetExportedSpriteName() const;
  bool IsVisible() const;

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
};
