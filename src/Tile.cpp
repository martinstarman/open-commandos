#include "Tile.h"

namespace GreenBeret
{
    Tile::Tile(int x, int y, int w, int h, int offsetX, int offsetY, int brightness,
               const std::string &fileName, const std::string &transformation)
        : position(x, y),
          w(w),
          h(h),
          offset(offsetX, offsetY),
          brightness(brightness),
          fileName(fileName),
          transformation(transformation)
    {
    }

    Tile::~Tile() = default;
} // namespace GreenBeret
