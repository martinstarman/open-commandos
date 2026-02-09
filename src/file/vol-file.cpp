#include "node.h"
#include <raylib.h>
#include <string>
#include <vector>
#include "vol-file.h"

VolFile::VolFile(const std::string &path)
{
  TraceLog(LOG_INFO, ("FILE: Opening .vol file " + path).c_str());
  Open(path);
}

VolFile::~VolFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .vol file");
  file.close();
  delete root;
}

void VolFile::Parse()
{
  ReadUntil('\n'); // read first line
  root = ReadNode();

  TraceLog(LOG_INFO, std::to_string(root->GetNode("MAPDIMXY")->GetListOfNumbers().at(0)).c_str());
  TraceLog(LOG_INFO, std::to_string(root->GetNode("MAPDIMXY")->GetListOfNumbers().at(1)).c_str());
}

bool VolFile::IsClosingBracket(char c) const
{
  return c == '}';
}

bool VolFile::IsSemicolon(char c) const
{
  return c == ';';
}

Node *VolFile::ReadNode()
{
  Node *node = new Node();

  while (!IsClosingBracket(Peek()))
  {
    ReadWhiteSpaces();

    if (IsSemicolon(Peek()))
    {
      ReadUntil('\n');
    }
    else if (IsString(Peek()))
    {
      std::string keyword = ReadString();
      ReadWhiteSpaces();

      if (keyword == "MAPDIMXY")
      {
        Node *value = ReadMapDimensions();
        node->SetNode(keyword, value);
      }
      else if (keyword == "MAPTABPOLYS")
      {
        Node *value = ReadMapDimensions();
        node->SetNode(keyword, value);
      }
    }
  }

  return node;
}

Node *VolFile::ReadMapDimensions()
{
  Node *node = new Node();
  ReadWhiteSpaces();
  double x = ReadNumber();
  ReadWhiteSpaces();
  Get(); // read ','
  ReadWhiteSpaces();
  double y = ReadNumber();
  ReadWhiteSpaces();
  std::vector<double> listOfNumbers{x, y};
  node->SetListOfNumbers(listOfNumbers);
  return node;
}

Node *VolFile::ReadMapPolygons()
{
  Node *node = new Node();
  //
  return node;
}
