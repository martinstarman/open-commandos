#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include <vector>
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
  std::cout << "OUT: x:" << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".XY")->GetIntVec().at(0) << "\n";
  std::cout << "OUT: y:" << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".XY")->GetIntVec().at(1) << "\n";
  std::cout << "OUT: " << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".BITMAP")->GetString() << "\n";
  std::cout << "OUT: x:" << root->GetChild(".FASE0000")->GetChild(".XYZ")->GetIntVec().at(0) << "\n";
  std::cout << "OUT: y:" << root->GetChild(".FASE0000")->GetChild(".XYZ")->GetIntVec().at(1) << "\n";
  std::cout << "OUT: z:" << root->GetChild(".FASE0000")->GetChild(".XYZ")->GetIntVec().at(2) << "\n";
  std::cout << "OUT: v1:" << root->GetChild(".FASE0000")->GetChild(".ARRAY")->GetNodeVec()[0]->GetChild(".STR")->GetString() << "\n";
  std::cout << "OUT: v2:" << root->GetChild(".FASE0000")->GetChild(".ARRAY")->GetNodeVec()[1]->GetChild(".STR")->GetString() << "\n";
  std::cout << "OUT: v3:" << root->GetChild(".FASE0000")->GetChild(".ARRAY")->GetNodeVec()[2]->GetChild(".STR")->GetString() << "\n";
}

bool MisFile::IsNumber(char c) const
{
  return c == '-' || (c >= '0' && c <= '9');
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
    else if (IsNumber(c)) // TODO: handle decimal numbers (.SCALE)
    {
      int number = ReadNumber();
      Node *child = new Node();
      child->SetNumber(number);
      node->SetChild(key, child);
      key = "";
    }
    else if (c == '[')
    {
      misFile.get();

      if (IsNumber(Peek()))
      {
        std::vector<int> intVec = ReadIntVec();
        Node *child = new Node();
        child->SetIntVec(intVec);
        node->SetChild(key, child);
      }
      else if (Peek() == '[')
      {
        std::vector<Node *> nodeVec = ReadNodeVec();
        Node *child = new Node();
        child->SetNodeVec(nodeVec);
        node->SetChild(key, child);
      }
      else
      {
        node->SetChild(key, ReadNode());
      }

      key = "";
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

std::vector<int> MisFile::ReadIntVec()
{
  std::vector<int> intVec;

  while (misFile.peek() != ']')
  {
    if (isspace(misFile.peek()))
    {
      misFile.get();
    }
    else
    {
      intVec.push_back(ReadNumber());
    }
  }

  misFile.get(); // consume ']'

  return intVec;
}

std::vector<Node *> MisFile::ReadNodeVec()
{
  std::vector<Node *> nodeVec;

  while (misFile.peek() != ']')
  {
    if (misFile.peek() == '[')
    {
      misFile.get();
      nodeVec.push_back(ReadNode());
    }
    else
    {
      misFile.get();
    }
  }

  misFile.get(); // consume ']'

  return nodeVec;
}
