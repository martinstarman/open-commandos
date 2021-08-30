#pragma once

#include <fstream>
#include <string>

namespace GreenBeret
{
    class DIRFile
    {
    public:
        DIRFile(const std::string &path);
        ~DIRFile();
        void Extract();

    private:
        void ReadDir(const std::string &dirName, int dirOffset);
        std::ifstream file;
    };
} // namespace GreenBeret
