#include "area.h"

Area::Area(const std::string &name, const std::vector<std::tuple<int, int>> &sectors) : name(name),
                                                                                 sectors(sectors)
{
}

Area::~Area() = default;
