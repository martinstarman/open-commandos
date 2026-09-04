#pragma once

#include <raylib.h>
#include <string>

#include "bracket_file.h"

class DatFile : public BracketFile
{
public:
  DatFile(const std::string &path);
  ~DatFile();
};
