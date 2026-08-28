#pragma once

#include <raylib.h>
#include <string>

#include "mis_file.h"
#include "sec_file.h"
#include "vol_file.h"

class Mission
{
public:
  Mission();
  ~Mission();
  void Load(const std::string &name);
  void Update();
  void Render();

private:
  MisFile *misFile;
  VolFile *volFile;
  SecFile *secFile;
  int offsetX;
  int offsetY;
  void LoadTiles();
};
