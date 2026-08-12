#pragma once

#include <string>
#include <tuple>
#include <vector>

class Area
{
public:
  Area(const std::string &name, const std::vector<std::tuple<int, int>> &sectors);
  ~Area();

private:
  std::string name;
  std::vector<std::tuple<int, int>> sectors;
};
