#pragma once

#include <string>
#include <vector>

namespace GreenBeret
{
    int GetBufferValue(std::vector<char> buffer);
    std::string &replace(std::string &str, const std::string &subStr, const std::string &newSubStr);
    std::string &trim(std::string &str);
    std::vector<std::string> split(const std::string &s, char delim);
} // namespace GreenBeret