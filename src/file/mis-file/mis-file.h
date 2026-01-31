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
  bool IsOpeningBracket(int c) const;
  bool IsString(int c) const;
  bool IsNumber(int c) const;
  int ReadWhiteSpaces();
  std::string ReadKeyword();
  Node *ReadValue();
  Node *ReadNode();
  std::string ReadString();
  double ReadNumber();
  std::vector<double> ReadListOfNumbers();
  std::vector<std::vector<double>> ReadListOfNumberLists();
  std::vector<Node *> ReadNodeList();
  Node *ReadAbility();
  std::vector<std::string> ReadListOfAbilities();
  void ReadClosingBracket();
};
