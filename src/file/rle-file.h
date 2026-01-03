#pragma once

#include <string>
#include <vector>

class RleFile
{
public:
  RleFile(std::string path);
  ~RleFile();
  void WriteFrom(std::vector<char> &buffer, std::vector<std::vector<char>> palettes);
  int Size();

private:
  std::string path;
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
