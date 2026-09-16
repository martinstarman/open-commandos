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
  const std::string &GetSpriteName() const;
  const Rectangle GetRect(int cameraOffsetX, int cameraOffsetY) const;
  const bool IsVisible() const;
  const bool IsFlippedX() const;
  const bool IsFlippedY() const;
  const double GetX() const;
  const double GetY() const;
  const double GetWidth() const;
  const double GetHeight() const;
  const double GetOffsetX() const;
  const double GetOffsetY() const;

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
  bool isVisible;
  bool isFlippedX;
  bool isFlippedY;
};
