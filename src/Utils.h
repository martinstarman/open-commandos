#pragma once
#include "PointF.h"
#include <string>
#include <vector>

namespace GreenBeret
{
    int GetBufferValue(std::vector<char> buffer);
    PointF ToWindowPoint(const PointF point);
    std::string& trim(std::string& s);
    std::vector<std::string> split(const std::string &s, char delim);
} // namespace GreenBeret