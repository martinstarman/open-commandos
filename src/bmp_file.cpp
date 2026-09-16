#include "bmp_file.h"

BmpFile::BmpFile()
    : image(new Image({})),
      size(0),
      height(0),
      width(0)
{
}

BmpFile::~BmpFile() = default;

Image *BmpFile::Load(std::vector<char> &buffer, std::vector<std::vector<char>> palettes)
{
  int offset = 0;

  std::vector<char> nameBuffer(
      buffer.begin() + offset,
      buffer.begin() + offset + blockFileNameSize);
  name = std::string(nameBuffer.begin(), nameBuffer.end());
  name.erase(std::find(name.begin(), name.end(), '\0'), name.end());

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

  pixels.clear();

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

  unsigned char *data = new unsigned char[pixels.size()];
  std::copy(pixels.begin(), pixels.end(), data);

  image->data = data;
  image->width = width;
  image->height = height;
  image->mipmaps = 1;
  image->format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

  size = blockHeaderSize + pixelsCount + blockPaletteIndexSize;

  return image;
}

int BmpFile::GetSize()
{
  return size;
}

const std::string &BmpFile::GetName() const
{
  return name;
}
