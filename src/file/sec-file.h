#pragma once

#include <raylib.h>
#include <string>
#include <tuple>
#include <vector>

#include "area.h"
#include "sector.h"
#include "text-file.h"

class SecFile : public TextFile
{
public:
  SecFile(const std::string &path);
  ~SecFile();
  void Parse() override;

private:
  std::vector<std::tuple<double, double>> vertices;
  std::vector<Sector> sectors;
  std::vector<Sector> bridgeSectors;
  std::vector<Area> areas;
  std::vector<std::tuple<int, int>> connectedSectors;
};
