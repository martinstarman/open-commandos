#include "bmp-file.h"

BmpFile::BmpFile()
    : size(0),
      height(0),
      width(0)
{
}

BmpFile::~BmpFile() = default;

void BmpFile::Load(std::vector<char> &buffer, std::vector<std::vector<char>> palettes)
{
  int offset = 0;

  std::vector<char> nameBuffer(
      buffer.begin() + offset,
      buffer.begin() + offset + blockFileNameSize);
  name = std::string(nameBuffer.begin(), nameBuffer.end());

  offset += blockFileNameSize;

  std::vector<char> pixelsCountBuffer(
      buffer.begin() + offset,
      buffer.begin() + offset + blockPixelsCountSize);
  int pixelsCount = GetBufferValue(pixelsCountBuffer);

  offset += blockPixelsCountSize + blockUnknown1Size;

  std::vector<char> heightBuffer(
      buffer.begin() + offset,
      buffer.begin() + offset + blockHeightSize);
  height = GetBufferValue(heightBuffer);
  offset += blockHeightSize;

  std::vector<char> widthBuffer(
      buffer.begin() + offset,
      buffer.begin() + offset + blockWidthSize);
  width = GetBufferValue(widthBuffer);
  offset += blockWidthSize + blockColorDepthSize + blockUnknown2Size;

  std::vector<unsigned char> pixelsBuffer(
      buffer.begin() + offset,
      buffer.begin() + offset + pixelsCount);

  offset += pixelsCount;

  std::vector<char> paletteIndexBuffer(
      buffer.begin() + offset,
      buffer.begin() + offset + blockPaletteIndexSize);
  int paletteIndex = GetBufferValue(paletteIndexBuffer);

  std::vector<char> palette = palettes.at(paletteIndex);

  std::vector<unsigned char> pixels;

  for (int i = 0; i < pixelsBuffer.size() - 1; i++) // skip last byte in image
  {
    if (i % (width + 2) == width || i % (width + 2) == width + 1) // skip last 2 bytes on every line
    {
      continue;
    }

    int pixelIndex = pixelsBuffer.at(i);

    unsigned char firstByte = palette.at(pixelIndex * 2);      // GGGBBBBB
    unsigned char secondByte = palette.at(pixelIndex * 2 + 1); // RRRRRGGG
    int color = (int)secondByte << 8 | firstByte;              // RRRRRGGGGGGBBBBB
    int red = (color & 0xF800) >> 8;                           // RRRRR000
    int green = (color & 0x07E0) >> 3;                         // GGGGGG00
    int blue = (color & 0x001F) << 3;                          // BBBBB000

    pixels.push_back(red);
    pixels.push_back(green);
    pixels.push_back(blue);
    pixels.push_back(255);
  }

  image.data = &pixels[0];
  image.width = width;
  image.height = height;
  image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

  size = blockHeaderSize + pixelsCount + blockPaletteIndexSize;
}

void BmpFile::Export(std::string path)
{
  std::string imageName = Replace(name, "BMP", "png");
  std::string imagePath = path.append("/").append(imageName);
  ExportImage(image, imagePath.c_str());
}

int BmpFile::GetSize()
{
  return size;
}
