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
  std::vector<char> buffer;
  int pointer;
  char Peek();
  char Get();
  void Unget();
  Node *root;
  bool IsOpeningBracket(char c) const;
  bool IsString(char c) const;
  bool IsNumber(char c) const;
  int ReadWhiteSpaces();
  std::string ReadKeyword();
  Node *ReadValue();
  Node *ReadNode();
  std::string ReadString();
  double ReadNumber();
  std::vector<double> ReadListOfNumbers();
  std::vector<std::vector<double>> ReadListOfNumberLists();
  std::vector<Node *> ReadListOfNodes();
  Node *ReadAbility();
  std::vector<std::string> ReadListOfAbilities();
  void ReadClosingBracket();
  void ReadUntil(char c);
};
