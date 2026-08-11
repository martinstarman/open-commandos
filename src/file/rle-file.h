#pragma once

#include <raylib.h>
#include <string>
#include <vector>

#include "../utils.h"

class RleFile
{
public:
  RleFile();
  ~RleFile();
  void Load(std::vector<char> &buffer, std::vector<std::vector<char>> palettes);
  void Export(std::string path);
  int GetSize();

private:
  Image image;
  std::string name;
  int size;
  int blockHeaderSize = 64;
  int blockFileNameSize = 32;
  int blockPixelsCountSize = 8;
  int blockUnknown1Size = 8;
  int blockHeightSize = 4;
  int blockWidthSize = 4;
  int blockColorDepthSize = 2;
  int blockUnknown2Size = 6;
  int blockLineOffsetsHeaderSize = 16;
  int blockLineOffsetSize = 4;
  int blockPaletteIndexSize = 4;
  enum PixelType
  {
    Transparent = 255,
    SemiTransparent = 254,
  };
};
