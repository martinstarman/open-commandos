#pragma once

#include <fstream>
#include <string>
#include <vector>

class TextFile
{
public:
  TextFile();
  ~TextFile();
  virtual void Parse();

protected:
  std::ifstream file;
  std::vector<char> buffer;
  int pointer;
  void Open(const std::string &path);
  char Peek();
  char Get();
  void Unget();
  bool IsNumber(char c) const;
  bool IsString(char c) const;
  void ReadUntil(char c);
  int ReadWhiteSpaces();
  double ReadNumber();
  std::string ReadString();
};
