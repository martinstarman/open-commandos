#pragma once

#include "node.h"
#include <string>
#include "text-file.h"
#include <vector>

class VolFile : public TextFile
{
public:
  VolFile(const std::string &path);
  ~VolFile();
  void Parse() override;

private:
  Node *root;
  bool IsClosingBracket(char c) const;
  bool IsSemicolon(char c) const;
  Node *ReadNode();
  Node *ReadMapDimensions();
  Node *ReadMapPolygons(); 
  void ReadComma();
  void ReadComment();
  std::string ReadQuotedString();
};
