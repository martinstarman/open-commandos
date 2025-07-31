#include <string>
#include <vector>

#include "rle_file.h"
#include "utils.h"

RleFile::RleFile()
    : size(0)
{
}

RleFile::~RleFile()
{
}

void RleFile::WriteFrom(std::vector<char> &buffer)
{
  int offset = 0;

  std::vector<char> nameBuffer(buffer.begin() + offset, buffer.begin() + offset + blockFileNameSize);
  std::string name(nameBuffer.begin(), nameBuffer.end());

  offset += blockFileNameSize;

  std::vector<char> pixelsCountBuffer(buffer.begin() + offset, buffer.begin() + offset + blockPixelsCountSize);
  int pixelsCount = GetBufferValue(pixelsCountBuffer);

  offset += blockPixelsCountSize;
  offset += 8; // TODO: unknown

  std::vector<char> heightBuffer(buffer.begin() + offset, buffer.begin() + offset + blockHeightSize);
  int height = GetBufferValue(heightBuffer);

  size = blockHeaderSize + pixelsCount + blockLineOffsetsSize + (height * 4) + blockPaletteIndexSize;
  // TODO: write file
}

int RleFile::Size()
{
  return size;
}
