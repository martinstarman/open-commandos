#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "vol-file-node.h"

class VolFile
{
public:
  VolFile(const std::string &path);
  ~VolFile();
  void Parse();

private:
  std::ifstream volFile;
  VolFileNode *root;
  std::vector<char> buffer;
  int pointer;
  char Peek();
  char Get();
  void Unget();
  bool IsClosingBracket(char c) const;
  bool IsString(char c) const;
  bool IsSemicolon(char c) const;
  bool IsNumber(char c) const;
  void ReadUntil(char c);
  int ReadWhiteSpaces();
  VolFileNode *ReadNode();
  std::string ReadKeyword();
  int ReadNumber();
};
