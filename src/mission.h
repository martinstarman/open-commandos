#pragma once

#include <algorithm>
#include <raylib.h>
#include <string>
#include <vector>

#include "mis_file.h"
#include "polygon.h"
#include "sec_file.h"
#include "vol_file.h"

class Mission
{
public:
  Mission();
  ~Mission();
  void Load(const std::string &name);
  void Update();
  void Render() const;
  int GetWidth() const;
  int GetHeight() const;

private:
  int width;
  int height;
  MisFile *misFile;
  VolFile *volFile;
  SecFile *secFile;
  int offsetX;
  int offsetY;
  std::vector<Polygon *> sortedPolygons;
  void LoadTiles();
};
