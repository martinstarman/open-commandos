#include "dir_file.h"

DirFile::DirFile(const std::string &path)
{
  TraceLog(LOG_INFO, ("FILE: Opening .dir file " + path).c_str());
  dirFile.open(path, std::ifstream::binary);
}

DirFile::~DirFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .dir file");
  dirFile.close();
}

void DirFile::Extract()
{
  ExtractDirectory(std::filesystem::current_path(), 0);
}

void DirFile::ExtractDirectory(std::filesystem::path path, int directoryOffset)
{
  std::vector<char> buffer;
  int directoryCount = 0;
  int entryType = EntryType::File;

  while (entryType != EntryType::DirectoryEnd)
  {
    int offset = directoryOffset + (blockEntrySize * directoryCount);
    directoryCount++;

    buffer.resize(blockNameSize);
    dirFile.seekg(offset, dirFile.beg);
    dirFile.read(&buffer[0], blockNameSize);
    std::string entryName(buffer.begin(), buffer.end());
    entryName.erase(std::find(entryName.begin(), entryName.end(), '\0'), entryName.end());

    offset += blockNameSize;

    buffer.resize(blockTypeSize);
    dirFile.seekg(offset, dirFile.beg);
    dirFile.read(&buffer[0], blockTypeSize);
    entryType = (int)buffer.at(0);

    offset += blockTypeSize;
    offset += blockPaddingSize;

    buffer.resize(blockSizeSize);
    dirFile.seekg(offset, dirFile.beg);
    dirFile.read(&buffer[0], blockSizeSize);
    int entrySize = GetBufferValue(buffer);

    offset += blockSizeSize;

    buffer.resize(blockOffsetSize);
    dirFile.seekg(offset, dirFile.beg);
    dirFile.read(&buffer[0], blockOffsetSize);
    int entryOffset = GetBufferValue(buffer);

    if (entryType == EntryType::DirectoryEnd)
    {
      TraceLog(LOG_INFO, "    > All files in directory extracted");
    }
    else if (entryType == EntryType::File)
    {
      if (entrySize > 0)
      {
        std::filesystem::path filePath = path / entryName;
        TraceLog(LOG_INFO, ("    > Writing file " + filePath.string()).c_str());
        std::fstream file(filePath.string(), std::ios::out | std::ios::binary);
        buffer.resize(entrySize);
        dirFile.seekg(entryOffset, dirFile.beg);
        dirFile.read(&buffer[0], entrySize);
        file.write(&buffer[0], buffer.size());
        file.close();
      }
    }
    else if (entryType == EntryType::Directory)
    {
      std::filesystem::path directoryPath = path / entryName;
      TraceLog(LOG_INFO, ("    > Creating directory " + directoryPath.string()).c_str());
      std::filesystem::create_directory(directoryPath);
      ExtractDirectory(directoryPath, entryOffset);
    }
  }
}
