#pragma once

#include <fstream>
#include <string>
#include <tuple>
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
  char Peek();
  void ReadSpaces();
  std::string ReadString();
  int ReadNumber();
  Node *ReadNode();
  // TODO: parse as vector of integers
  std::tuple<int, int> ReadVec2();
  std::tuple<int, int, int> ReadVec3();
  std::vector<Node *> ReadNodeVec();
};
