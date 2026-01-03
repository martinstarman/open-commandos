#include <algorithm>
#include <string>

#include "bmp_file.h"
#include "raylib.h"
#include "rle_file.h"
#include "utils.h"
#include "wad_file.h"

WadFile::WadFile(std::string path)
{
  TraceLog(LOG_INFO, ("UTILS: Opening .wad file " + path).c_str());
  wadFile.open(path, std::ifstream::binary);
}

WadFile::~WadFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .wad file");
  wadFile.close();
}

void WadFile::Extract()
{
  std::vector<char> buffer;
  int offset = blockHeaderSize; // skip header block

  wadFile.seekg(0, wadFile.end);
  int wadFileSize = (int)wadFile.tellg();

  buffer.resize(blockPalettesCountSize);
  wadFile.seekg(offset, wadFile.beg);
  wadFile.read(&buffer[0], blockPalettesCountSize);
  int palettesCount = GetBufferValue(buffer);

  offset += blockPalettesCountSize;

  std::vector<std::vector<char>> palettes;
  palettes.resize(palettesCount);
  buffer.resize(blockPaletteSize);
  for (int i = 0; i < palettesCount; i++)
  {
    wadFile.seekg(offset, wadFile.beg);
    wadFile.read(&buffer[0], blockPaletteSize);
    palettes.at(i) = buffer;

    offset += blockPalettesSize;
  }

  buffer.resize(blockImagesCountSize);
  wadFile.seekg(offset, wadFile.beg);
  wadFile.read(&buffer[0], blockImagesCountSize);
  int images = GetBufferValue(buffer);

  offset += blockImagesCountSize;
  int imageFileNameSize = 32;

  while (offset < wadFileSize)
  {
    buffer.resize(imageFileNameSize);
    wadFile.seekg(offset, wadFile.beg);
    wadFile.read(&buffer[0], imageFileNameSize);
    std::string name(buffer.begin(), buffer.end());
    name.erase(std::find(name.begin(), name.end(), '\0'), name.end());

    if (name.compare(name.length() - 3, 3, "BMP") == 0)
    {
      buffer.resize(wadFileSize - offset);
      wadFile.seekg(offset, wadFile.beg);
      wadFile.read(&buffer[0], wadFileSize - offset);

      BmpFile bmpFile = BmpFile();
      bmpFile.WriteFrom(buffer, palettes);

      offset += bmpFile.Size();
    }
    else
    {
      buffer.resize(wadFileSize - offset);
      wadFile.seekg(offset, wadFile.beg);
      wadFile.read(&buffer[0], wadFileSize - offset);

      RleFile rleFile = RleFile();
      rleFile.WriteFrom(buffer, palettes);

      offset += rleFile.Size();
    }
  }
}
