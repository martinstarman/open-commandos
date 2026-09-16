#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
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
  void ExportImages();
  std::map<std::string, Texture *> GetTextures();

private:
  std::string path;
  std::string wadFileDirectory;
  std::ifstream wadFile;
  int blockHeaderSize = 400;
  int blockPalettesCountSize = 4;
  int blockPalettesSize = 525;
  int blockPaletteSize = 512;
  int blockImagesCountSize = 4;
  std::map<std::string, Image *> images;
  void LoadImages();
};
