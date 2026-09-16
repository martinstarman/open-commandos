#pragma once

#include <algorithm>
#include <raylib.h>
#include <string>
#include <vector>

#include "utils.h"

class BmpFile
{
public:
  BmpFile();
  ~BmpFile();
  void Load(std::vector<char> &buffer, std::vector<std::vector<char>> palettes);
  void Export(std::string path);
  Texture* GetTexture();
  int GetSize();
  const std::string &GetName() const;
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
  Image image;
  std::string name;
  std::vector<unsigned char> pixels;
  int size;
  int height;
  int width;
};
