#include "Utils.h"

#include "Map.h"

#include <iostream>
#include <math.h>
#include <regex>
#include <sstream>
#include <vector>

namespace GreenBeret
{
    int GetBufferValue(std::vector<char> buffer)
    {
        int value = 0;

        for (int i = 0; i < buffer.size(); i++)
        {
            value |= (unsigned char)buffer.at(i) << i * 8;
        }

        return value;
    }

    std::string &replace(std::string &str, const std::string &subStr, const std::string &newSubStr)
    {
        str = std::regex_replace(str, std::regex(subStr), newSubStr);
        return str;
    }

    std::string &trim(std::string &str)
    {
        str = replace(str, "^\\s+", "");
        str = replace(str, "\\s+$", "");
        return str;
    }

    std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (std::getline(ss, item, delim))
        {
            result.push_back(item);
        }

        return result;
    }
} // namespace GreenBeret