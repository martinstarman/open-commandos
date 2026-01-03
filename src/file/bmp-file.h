#pragma once

#include <string>
#include <vector>

class BmpFile
{
public:
  BmpFile(std::string path);
  ~BmpFile();
  void WriteFrom(std::vector<char> &buffer, std::vector<std::vector<char>> palettes);
  int Size();
  int blockHeaderSize = 64;
  int blockFileNameSize = 32;
  int blockPixelsCountSize = 8;
  int blockUnknown1Size = 8;
  int blockHeightSize = 4;
  int blockWidthSize = 4;
  int blockColorDepthSize = 2;
  int blockUnknown2Size = 6;
  int blockPaletteIndexSize = 4;

private:
  std::string path;
  int size;
  int height;
  int width;
};
