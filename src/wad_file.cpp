#include "wad_file.h"

WadFile::WadFile(const std::string &path)
    : path(path),
      wadFileDirectory(std::filesystem::path(path).parent_path().string())
{
  TraceLog(LOG_INFO, ("FILE: Opening .wad file " + path).c_str());
  wadFile.open(path, std::ifstream::binary);
  LoadImages();
}

WadFile::~WadFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .wad file");

  for (const auto &[_, image] : images)
  {
    delete[] image->data;
    delete image;
  }

  wadFile.close();
}

void WadFile::LoadImages()
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
  int imagesCount = GetBufferValue(buffer);

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
      Image *image = bmpFile.Load(buffer, palettes);
      images.emplace(bmpFile.GetName(), image);

      offset += bmpFile.GetSize();
    }
    else
    {
      buffer.resize(wadFileSize - offset);
      wadFile.seekg(offset, wadFile.beg);
      wadFile.read(&buffer[0], wadFileSize - offset);

      RleFile rleFile = RleFile();
      Image *image = rleFile.Load(buffer, palettes);
      images.emplace(rleFile.GetName(), image);

      offset += rleFile.GetSize();
    }
  }
}

void WadFile::ExportImages()
{
  for (const auto &[name, image] : images)
  {
    std::string imageName = name;
    imageName = Replace(imageName, "BMP", "png");
    imageName = Replace(imageName, "RLE", "png");
    std::string path = wadFileDirectory;
    path.append("/").append(imageName);
    ExportImage(*image, path.c_str());
  }
}

std::map<std::string, Texture *> WadFile::GetTextures()
{
  std::map<std::string, Texture *> textures;

  for (const auto &[name, image] : images)
  {
    Texture *texture = new Texture(LoadTextureFromImage(*image));
    SetTextureWrap(*texture, TEXTURE_WRAP_REPEAT);
    textures.emplace(name, texture);
  }

  return textures;
}
