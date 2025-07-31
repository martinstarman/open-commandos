#pragma once

#include <fstream>
#include <string>

class WadFile
{
public:
  WadFile(std::string path);
  ~WadFile();
  void Extract();

private:
  std::ifstream wadFile;
  int blockHeaderSize = 400;
  int blockPalettesCountSize = 4;
  int blockPalettesSize = 525;
  int blockPaletteSize = 512;
  int blockImagesCountSize = 4;
};
