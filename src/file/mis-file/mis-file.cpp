#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include "mis-file.h"
#include "node.h"

// temp
#include <iostream>

MisFile::MisFile(const std::string &path)
{
  TraceLog(LOG_INFO, ("FILE: Opening .mis file " + path).c_str());
  misFile.open(path, std::ifstream::in);
}

MisFile::~MisFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .mis file");
  misFile.close();
  delete root;
}

void MisFile::Parse()
{
  root = ReadNode();

  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".DATOSFICHEROSMISION")->GetChild(".VOLUMENES")->GetString() << "\n";
  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".DATOSFICHEROSMISION")->GetChild(".INTROSCRIPT")->GetString() << "\n";
  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".X")->GetNumber() << "\n";
  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".TEST")->GetChild(".A")->GetString() << "\n";
  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".TEST")->GetChild(".B")->GetString() << "\n";
  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".Y")->GetNumber() << "\n";
  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".SCALE")->GetNumber() << "\n";
  std::cout << "OUT: x:" << std::get<0>(root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".XY")->GetVec2()) << "\n";
  std::cout << "OUT: y:" << std::get<1>(root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".XY")->GetVec2()) << "\n";
  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".BITMAP")->GetString() << "\n";
  std::cout << "OUT: x:" << std::get<0>(root->GetChild(".FASE0000")->GetChild(".XYZ")->GetVec3()) << "\n";
  std::cout << "OUT: y:" << std::get<1>(root->GetChild(".FASE0000")->GetChild(".XYZ")->GetVec3()) << "\n";
  std::cout << "OUT: z:" << std::get<2>(root->GetChild(".FASE0000")->GetChild(".XYZ")->GetVec3()) << "\n";
}

char MisFile::Peek()
{
  ReadSpaces();
  return misFile.peek();
}

void MisFile::ReadSpaces()
{
  while (isspace(misFile.peek()))
  {
    misFile.get();
  }
}

std::string MisFile::ReadString()
{
  std::string string;

  while (!isspace(misFile.peek()))
  {
    string.push_back(misFile.get());
  }

  return string;
}

int MisFile::ReadNumber()
{
  return atoi(ReadString().c_str());
}

Node *MisFile::ReadNode()
{
  Node *node = new Node();
  std::string key = "";

  while (!misFile.eof())
  {
    char c = misFile.peek();

    if (isspace(c) || c == EOF)
    {
      misFile.get();
    }
    else if (c == '.' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
      std::string string = ReadString();

      if (key == "")
      {
        key = string;
      }
      else
      {
        Node *child = new Node();
        child->SetString(string);
        node->SetChild(key, child);
        key = "";
      }
    }
    else if (c == '-' || (c >= '0' && c <= '9')) // TODO: handle decimal numbers (.SCALE)
    {
      int number = ReadNumber();
      Node *child = new Node();
      child->SetNumber(number);
      node->SetChild(key, child);
      key = "";
    }
    else if (c == '[')
    {
      if (key == ".XY")
      {
        misFile.get();
        std::tuple<int, int> vec2 = ReadVec2();
        Node *child = new Node();
        child->SetVec2(vec2);
        node->SetChild(key, child);
        key = "";
      }
      else if (key == ".XYZ")
      {
        misFile.get();
        std::tuple<int, int, int> vec3 = ReadVec3();
        Node *child = new Node();
        child->SetVec3(vec3);
        node->SetChild(key, child);
        key = "";
      }
      else if (Peek() == '[')
      {
        // TODO: parse vec
        std::cout << "VEC\n";
      }
      else
      {
        misFile.get();
        node->SetChild(key, ReadNode());
        key = "";
      }
    }
    else if (c == ']')
    {
      misFile.get();
      break;
    }
    else
    {
      std::cout << "Unknown character: " << misFile.get() << "\n";
    }
  }

  return node;
}

std::tuple<int, int> MisFile::ReadVec2()
{
  ReadSpaces();
  int x = ReadNumber();
  ReadSpaces();
  int y = ReadNumber();
  ReadSpaces();
  misFile.get(); // consume ']'

  return std::make_tuple(x, y);
}

std::tuple<int, int, int> MisFile::ReadVec3()
{
  ReadSpaces();
  int x = ReadNumber();
  ReadSpaces();
  int y = ReadNumber();
  ReadSpaces();
  int z = ReadNumber();
  ReadSpaces();
  misFile.get(); // consume ']'

  return std::make_tuple(x, y, z);
}
