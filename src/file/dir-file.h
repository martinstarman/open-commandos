#pragma once

#include <filesystem>
#include <fstream>
#include <string>

class DirFile
{
public:
  DirFile(std::string path);
  ~DirFile();
  void Extract();

private:
  std::ifstream dirFile;
  void ExtractDirectory(std::filesystem::path path, int directoryOffset);
  int blockEntrySize = 44;
  int blockNameSize = 32;
  int blockTypeSize = 1;
  int blockPaddingSize = 3;
  int blockSizeSize = 4;
  int blockOffsetSize = 4;
  enum EntryType
  {
    DirectoryEnd = -1,
    File = 0,
    Directory = 1,
  };
};
