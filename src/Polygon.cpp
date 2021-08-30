#include "Polygon.h"

#include <string>

namespace GreenBeret
{
    Polygon::Polygon(const std::string &name, float x, float y, int z, int h)
        : name(name),
          center(x, y),
          z(z),
          h(h),
          points({}),
          tiles({})
    {
    }

    Polygon::~Polygon() = default;
} // namespace GreenBeret
