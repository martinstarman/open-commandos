#include "DIRFile.h"

#include "Utils.h"

#include <filesystem>
#include <SDL.h>
#include <string>
#include <vector>

namespace GreenBeret
{
    DIRFile::DIRFile(const std::string &path)
    {
        SDL_Log("Opening DIR file: %s", path.c_str());
        file.open(path, std::ifstream::binary);
    }

    DIRFile::~DIRFile()
    {
        file.close();
    }

    void DIRFile::Extract()
    {
        ReadDir(std::filesystem::current_path().string(), 0);
    }

    void DIRFile::ReadDir(const std::string &dirName, int dirOffset)
    {
        std::vector<char> buffer;
        int i = 0;
        int type = 0;

        while (type != -1)
        {
            int currenOffset = dirOffset + (44 * i++);

            // name
            buffer.resize(32);
            file.seekg(currenOffset, file.beg);
            file.read(&buffer[0], 32);
            std::string name(buffer.begin(), buffer.end());
            name.erase(std::find(name.begin(), name.end(), '\0'), name.end());
            SDL_Log("File: %s", name.c_str());

            currenOffset += 32;

            // type
            buffer.resize(1);
            file.seekg(currenOffset, file.beg);
            file.read(&buffer[0], 1);
            type = (int)buffer.at(0);
            SDL_Log("File type: %i", type);

            currenOffset += 4;

            // size
            buffer.resize(4);
            file.seekg(currenOffset, file.beg);
            file.read(&buffer[0], 4);
            int size = GetBufferValue(buffer);
            SDL_Log("Size: %i", size);

            currenOffset += 4;

            // offset
            buffer.resize(4);
            file.seekg(currenOffset, file.beg);
            file.read(&buffer[0], 4);
            int offset = GetBufferValue(buffer);
            SDL_Log("Offset: %i", offset);

            if (type == -1)
            {
                SDL_Log("Directory end");
            }
            else if (type == 0)
            {
                if (size > 0)
                {
                    std::string fileName = dirName + "/" + name;
                    SDL_Log("Writing file: %s", fileName.c_str());
                    std::fstream outFile(fileName, std::ios::out | std::ios::binary);
                    buffer.resize(size);
                    file.seekg(offset, file.beg);
                    file.read(&buffer[0], size);
                    outFile.write(&buffer[0], buffer.size());
                    outFile.close();
                }
            }
            else if (type == 1)
            {
                std::string newDirName = dirName + "/" + name;
                SDL_Log("Creating dir: %s", newDirName.c_str());
                std::filesystem::create_directory(newDirName);
                ReadDir(newDirName, offset);
            }
        }
    }
} // namespace GreenBeret
