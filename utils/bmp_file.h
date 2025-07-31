#pragma once

#include <vector>

class BmpFile
{
public:
  BmpFile();
  ~BmpFile();
  void WriteFrom(std::vector<char> &buffer);
  int Size();
  int blockHeaderSize = 64;
  int blockFileNameSize = 32;
  int blockPixelsCountSize = 8;
  int blockPaletteIndexSize = 4;

private:
  int size;
};
