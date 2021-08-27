#include "Polygon.h"
#include <string>

namespace GreenBeret
{
  Polygon::Polygon(const std::string &name, float x, float y, int z, int h, int vertices_no,
                   int tiles_no)
      : name(name),
        center(PointF(x, y)),
        z(z),
        h(h),
        vertices_no(vertices_no),
        tiles_no(tiles_no),
        points({})
  {
  }

  Polygon::~Polygon() = default;
} // namespace GreenBeret
