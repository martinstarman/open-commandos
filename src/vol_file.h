#pragma once

#include <raylib.h>
#include <string>
#include <vector>

#include "node.h"
#include "polygon.h"
#include "text_file.h"

class VolFile : public TextFile
{
public:
  VolFile(const std::string &path);
  ~VolFile();
  void Parse() override;
  std::vector<Polygon> GetPolygons();

private:
  Node *root;
  std::vector<Polygon> polygons;
  bool IsClosingBracket(char c) const;
  bool IsSemicolon(char c) const;
  Node *ReadNode();
  Node *ReadMapDimensions();
  Node *ReadMapPolygons();
  void ReadComma();
  void ReadComment();
  std::string ReadQuotedString();
};
