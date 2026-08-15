#pragma once

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

private:
  MisFile *misFile;
  VolFile *volFile;
  SecFile *secFile;
};
