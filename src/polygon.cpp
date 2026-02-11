#include "polygon.h"

Polygon::Polygon(const std::string &name, double centerX, double centerY, double centerZ, double height)
    : name(name),
      centerX(centerX),
      centerY(centerY),
      centerZ(centerZ),
      height(height)
{
}

Polygon::~Polygon()
{
}
