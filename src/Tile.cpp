#include "Tile.h"

namespace GreenBeret
{
    Tile::Tile(int x, int y, int w, int h, int offset_x, int offset_y, int brightness,
               const std::string &sprite, const std::string &transformation)
        : x(x),
          y(y),
          w(w),
          h(h),
          offset_x(offset_x),
          offset_y(offset_y),
          brightness(brightness),
          sprite(sprite),
          transformation(transformation)
    {
    }

    Tile::~Tile() = default;
} // namespace GreenBeret
