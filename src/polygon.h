#pragma once

#include <string>

class Polygon
{
  public:
  Polygon(const std::string &name, double centerX, double centerY, double centerZ, double height);
  ~Polygon();

  private:
  std::string name;
  double centerX;
  double centerY;
  double centerZ;
  double height;
};
