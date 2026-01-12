#pragma once

#include <fstream>
#include <map>
#include <string>
#include "mis-value.h"

class MisFile
{
public:
  MisFile(std::string path);
  ~MisFile();
  void Parse();

private:
  std::ifstream misFile;
  std::string key;
  std::map<std::string, MisValue> parsed;
  std::string ReadString();
  int ReadNumber();

  // char Peek();
};
