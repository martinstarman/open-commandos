#pragma once

#include <fstream>
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
  MisValue* root;
  std::string ReadString();
  int ReadNumber();
  MisValue* ReadNode();

  // char Peek();
};
