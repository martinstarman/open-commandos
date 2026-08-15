#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <raylib.h>
#include <string>

#include "bmp_file.h"
#include "rle_file.h"
#include "utils.h"

class WadFile
{
public:
  WadFile(const std::string &path);
  ~WadFile();
  void Extract();

private:
  std::string path;
  std::ifstream wadFile;
  int blockHeaderSize = 400;
  int blockPalettesCountSize = 4;
  int blockPalettesSize = 525;
  int blockPaletteSize = 512;
  int blockImagesCountSize = 4;
};
