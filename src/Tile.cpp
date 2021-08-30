#include "Tile.h"

namespace GreenBeret
{
    Tile::Tile(float x, float y, float w, float h, float offsetX, float offsetY, int brightness,
               const std::string &fileName, const std::string &transformation)
        : position(x, y),
          size(w, h),
          offset(offsetX, offsetY),
          brightness(brightness),
          fileName(fileName),
          transformation(transformation)
    {
    }

    Tile::~Tile() = default;
} // namespace GreenBeret
