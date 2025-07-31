#include <string>
#include <vector>

#include "bmp_file.h"
#include "utils.h"

BmpFile::BmpFile()
    : size(0)
{
}

BmpFile::~BmpFile()
{
}

void BmpFile::WriteFrom(std::vector<char> &buffer)
{
  int offset = 0;

  std::vector<char> nameBuffer(buffer.begin() + offset, buffer.begin() + offset + blockFileNameSize);
  std::string name(nameBuffer.begin(), nameBuffer.end());

  offset += blockFileNameSize;

  std::vector<char> pixelsCountBuffer(buffer.begin() + offset, buffer.begin() + offset + blockPixelsCountSize);
  int pixelsCount = GetBufferValue(pixelsCountBuffer);

  size = blockHeaderSize + pixelsCount + blockPaletteIndexSize;

  // TODO: write file
}

int BmpFile::Size()
{
  return size;
}
