#pragma once

#include <string>
#include "text-file.h"
#include <vector>
#include "node.h"

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
};
