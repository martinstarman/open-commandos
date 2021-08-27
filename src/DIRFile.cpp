#include "DIRFile.h"
#include <filesystem>
#include <SDL.h>
#include <string>
#include "Utils.h"
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

    void DIRFile::ReadDir(const std::string &dir_name, int dir_offset)
    {
        std::vector<char> buffer;
        int i = 0;
        int type = 0;

        while (type != -1)
        {
            int curr_offset = dir_offset + (44 * i++);

            // name
            buffer.resize(32);
            file.seekg(curr_offset, file.beg);
            file.read(&buffer[0], 32);
            std::string name(buffer.begin(), buffer.end());
            name.erase(std::find(name.begin(), name.end(), '\0'), name.end());
            SDL_Log("File: %s", name.c_str());

            curr_offset += 32;

            // type
            buffer.resize(1);
            file.seekg(curr_offset, file.beg);
            file.read(&buffer[0], 1);
            type = (int)buffer.at(0);
            //SDL_Log("File type: %i", file_type);

            curr_offset += 4;

            // size
            buffer.resize(4);
            file.seekg(curr_offset, file.beg);
            file.read(&buffer[0], 4);
            int size = GetBufferValue(buffer);
            SDL_Log("Size: %i", size);

            curr_offset += 4;

            // offset
            buffer.resize(4);
            file.seekg(curr_offset, file.beg);
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
                    std::string file_name = dir_name + "/" + name;
                    SDL_Log("Writing file: %s", file_name.c_str());
                    std::fstream out_file(file_name, std::ios::out | std::ios::binary);
                    buffer.resize(size);
                    file.seekg(offset, file.beg);
                    file.read(&buffer[0], size);
                    out_file.write(&buffer[0], buffer.size());
                    out_file.close();
                }
            }
            else if (type == 1)
            {
                std::string new_dir_name = dir_name + "/" + name;
                SDL_Log("Creating dir: %s", new_dir_name.c_str());
                std::filesystem::create_directory(new_dir_name);
                ReadDir(new_dir_name, offset);
            }
        }
    }
} // namespace GreenBeret
