#pragma once

#include <vector>

class RleFile
{
public:
  RleFile();
  ~RleFile();
  void WriteFrom(std::vector<char> &buffer);
  int Size();

private:
  int size;
  int blockHeaderSize = 64;
  int blockFileNameSize = 32;
  int blockPixelsCountSize = 8;
  int blockLineOffsetsSize = 16;
  int blockPaletteIndexSize = 4;
  int blockHeightSize = 4;
};
