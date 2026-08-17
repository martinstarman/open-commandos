#pragma once

#include <map>
#include <raylib.h>
#include <string>

#include "mis_file.h"
#include "sec_file.h"
#include "utils.h"
#include "vol_file.h"

class Mission
{
public:
  Mission();
  ~Mission();
  void Load(const std::string &name);
  void Render();

private:
  MisFile *misFile;
  VolFile *volFile;
  SecFile *secFile;
  std::map<std::string, Texture> textures;
};
