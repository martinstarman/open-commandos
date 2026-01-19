#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "node.h"

class MisFile
{
public:
  MisFile(const std::string &path);
  ~MisFile();
  void Parse();

private:
  std::ifstream misFile;
  Node *root;
  bool IsNumber(char c) const;
  char Peek();
  void ReadSpaces();
  std::string ReadString();
  int ReadNumber();
  Node *ReadNode();
  std::vector<int> ReadIntVec();
  std::vector<Node *> ReadNodeVec();
};
