#include "sec_file.h"

SecFile::SecFile(const std::string &path)
{
  TraceLog(LOG_INFO, ("FILE: Opening .sec file " + path).c_str());
  Open(path);
}

SecFile::~SecFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .sec file");
  file.close();
}

void SecFile::Parse()
{
  ReadWhiteSpaces();
  int numberOfVertices = ReadNumber();

  for (size_t i = 0; i < numberOfVertices; ++i)
  {
    ReadWhiteSpaces();
    double x = ReadNumber();
    ReadWhiteSpaces();
    double y = ReadNumber();
    vertices.push_back(std::make_tuple(x, y));
  }

  ReadWhiteSpaces();
  int numberOfSectors = ReadNumber();

  for (size_t i = 0; i < numberOfSectors; ++i)
  {
    ReadWhiteSpaces();
    int numberOfSectorVertices = ReadNumber();
    ReadWhiteSpaces();
    double x = ReadNumber();
    ReadWhiteSpaces();
    double y = ReadNumber();
    ReadWhiteSpaces();
    double z = ReadNumber();
    ReadWhiteSpaces();
    int type = ReadNumber();
    ReadWhiteSpaces();
    int height = ReadNumber();
    ReadWhiteSpaces();
    int offset = ReadNumber();
    ReadWhiteSpaces();
    int flags = ReadNumber();

    std::vector<int> vertexIndexes;
    for (size_t j = 0; j < numberOfSectorVertices; ++j)
    {
      ReadWhiteSpaces();
      int index = ReadNumber();
      vertexIndexes.push_back(index);
    }

    sectors.push_back(Sector(numberOfSectorVertices, vertexIndexes, x, y, z, type, height, offset, flags));
  }

  ReadWhiteSpaces();
  int numberOfBridgeSectors = ReadNumber();

  for (size_t i = 0; i < numberOfBridgeSectors; ++i)
  {
    ReadWhiteSpaces();
    int numberOfBridgeSectorVertices = ReadNumber();
    ReadWhiteSpaces();
    double x = ReadNumber();
    ReadWhiteSpaces();
    double y = ReadNumber();
    ReadWhiteSpaces();
    double z = ReadNumber();
    ReadWhiteSpaces();
    int type = ReadNumber();
    ReadWhiteSpaces();
    int height = ReadNumber();
    ReadWhiteSpaces();
    int offset = ReadNumber();
    ReadWhiteSpaces();
    int flags = ReadNumber();

    std::vector<int> vertexIndexes;
    for (int j = 0; j < numberOfBridgeSectorVertices; ++j)
    {
      ReadWhiteSpaces();
      int index = ReadNumber();
      vertexIndexes.push_back(index);
    }

    bridgeSectors.push_back(Sector(numberOfBridgeSectorVertices, vertexIndexes, x, y, z, type, height, offset, flags));
  }

  ReadWhiteSpaces();
  int numberOfAreas = ReadNumber();

  for (size_t i = 0; i < numberOfAreas; ++i)
  {
    ReadWhiteSpaces();
    int numberOfAreaSectors = ReadNumber();
    ReadWhiteSpaces();
    std::string name = ReadString();
    std::vector<std::tuple<int, int>> sectors;

    for (size_t j = 0; j < numberOfAreaSectors; ++j)
    {
      ReadWhiteSpaces();
      int sectorType = ReadNumber();
      ReadWhiteSpaces();
      int sectorIndex = ReadNumber();
      sectors.push_back(std::make_tuple(sectorType, sectorIndex));
    }

    areas.push_back(Area(name, sectors));
  }

  ReadWhiteSpaces();
  int numberOfConectedSectors = ReadNumber();

  for (size_t i = 0; i < numberOfConectedSectors; ++i)
  {
    ReadWhiteSpaces();
    int sectorIndex1 = ReadNumber();
    ReadWhiteSpaces();
    int sectorIndex2 = ReadNumber();
    connectedSectors.push_back(std::make_tuple(sectorIndex1, sectorIndex2));
  }
}
