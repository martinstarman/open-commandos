#include <raylib.h>
#include <string>
#include <vector>

#include "node.h"
#include "../polygon.h"
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
    ReadComment();

    if (IsString(Peek()))
    {
      std::string keyword = ReadString();

      if (keyword == "MAPDIMXY")
      {
        Node *value = ReadMapDimensions();
        node->SetNode(keyword, value);
      }
      else if (keyword == "MAPTABPOLYS")
      {
        Node *value = ReadMapPolygons();
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
  ReadComma();
  double y = ReadNumber();
  ReadWhiteSpaces();
  std::vector<double> listOfNumbers{x, y};
  node->SetListOfNumbers(listOfNumbers);
  return node;
}

Node *VolFile::ReadMapPolygons()
{
  Node *node = new Node();

  ReadUntil('{');

  while (!IsClosingBracket(Peek()))
  {
    ReadWhiteSpaces();
    std::string keyword = ReadString();

    if (keyword == "POLY")
    {
      ReadWhiteSpaces();
      std::string name = ReadQuotedString();
      ReadComma();
      double centerX = ReadNumber();
      ReadComma();
      double centerY = ReadNumber();
      ReadComma();
      double centerZ = ReadNumber();
      ReadComma();
      double height = ReadNumber();
      ReadComma();
      double numberOfVertices = ReadNumber();
      ReadComma();
      double numberOfTiles = ReadNumber();
      ReadComment();

      Polygon polygon(name, centerX, centerY, centerZ, height, numberOfVertices, numberOfTiles);
      polygons.emplace_back(polygon);
    }
    else if (keyword == "RADIO")
    {
      ReadWhiteSpaces();
      double number = ReadNumber();
      ReadComment();

      // TODO
    }
    else if (keyword == "EXTRAINFO")
    {
      ReadWhiteSpaces();
      double n1 = ReadNumber();
      ReadComma();
      double n2 = ReadNumber();
      ReadComma();
      double n3 = ReadNumber();
      ReadComma();
      double n4 = ReadNumber();
      ReadComma();
      double n5 = ReadNumber();
      ReadComma();
      double n6 = ReadNumber();
      ReadComma();
      double n7 = ReadNumber();
      ReadComma();
      double n8 = ReadNumber();
      ReadComment();

      // TODO
    }
    else if (keyword == "TILE")
    {
      ReadWhiteSpaces();
      double x = ReadNumber();
      ReadComma();
      double y = ReadNumber();
      ReadComma();
      double width = ReadNumber();
      ReadComma();
      double height = ReadNumber();
      ReadComma();
      double offsetX = ReadNumber();
      ReadComma();
      double offsetY = ReadNumber();
      ReadComma();
      double brightness = ReadNumber();
      ReadComma();
      std::string spriteName = ReadQuotedString(); // TODO: visibility (starts with -)
      ReadComma();
      std::string transformation = ReadQuotedString();
      ReadComment();

      Tile tile(x, y, width, height, offsetX, offsetY, brightness, spriteName, transformation);
      polygons.back().AddTile(tile);
    }
    else if (keyword == "POINT")
    {
      ReadWhiteSpaces();
      double x = ReadNumber();
      ReadComma();
      double y = ReadNumber();
      ReadComment();

      polygons.back().AddPoint(x, y);
    }
    else if (keyword == "POLYRAMPA")
    {
      ReadUntil('\n'); // TODO
    }
    else
    {
      TraceLog(LOG_INFO, ("    > Unknown keyword " + keyword).c_str());
    }
  }

  return node;
}

std::string VolFile::ReadQuotedString()
{
  std::string string;
  ReadWhiteSpaces();
  Get(); // read "

  while (Peek() != '"')
  {
    string += Get();
  }

  Get(); // read "
  return string;
}

void VolFile::ReadComma()
{
  ReadWhiteSpaces();
  Get();
  ReadWhiteSpaces();
}

void VolFile::ReadComment()
{
  ReadWhiteSpaces();
  if (IsSemicolon(Peek()))
  {
    ReadUntil('\n');
  }
  ReadWhiteSpaces();
}

std::vector<Polygon> VolFile::GetPolygons()
{
  return polygons;
}
