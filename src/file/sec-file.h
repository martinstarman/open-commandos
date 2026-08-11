#pragma once

#include <raylib.h>
#include <string>

#include "text-file.h"

class SecFile : public TextFile
{
public:
  SecFile(const std::string &path);
  ~SecFile();
  void Parse() override;
};
