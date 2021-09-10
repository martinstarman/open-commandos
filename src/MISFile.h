#pragma once

#include <fstream>
#include <string>

namespace GreenBeret
{
    class MISFile
    {
    public:
        MISFile(const std::string &path);
        ~MISFile();
        void Parse();
        std::string volFileName;
        std::string secFileName;
    private:
        std::ifstream file;
        std::string ReadUntil(char c);
        void ParseMissionFiles(std::string &data);
    };
} // namespace GreenBeret