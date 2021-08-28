#include "Map.h"
#include "Utils.h"
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

    std::string &trim(std::string &s)
    {
        s = std::regex_replace(s, std::regex("\\s+"), "");
        return s;
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