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

  std::cout << "OUT  1: " << root->GetChild(".FASE0000")->GetChild(".DATOSFICHEROSMISION")->GetChild(".VOLUMENES")->GetString() << "\n";
  std::cout << "OUT  2: " << root->GetChild(".FASE0000")->GetChild(".DATOSFICHEROSMISION")->GetChild(".INTROSCRIPT")->GetString() << "\n";
  std::cout << "OUT  3: " << root->GetChild(".FASE0000")->GetChild(".X")->GetNumber() << "\n";
  std::cout << "OUT  4: " << root->GetChild(".FASE0000")->GetChild(".TEST")->GetChild(".A")->GetString() << "\n";
  std::cout << "OUT  5: " << root->GetChild(".FASE0000")->GetChild(".TEST")->GetChild(".B")->GetString() << "\n";
  std::cout << "OUT  6: " << root->GetChild(".FASE0000")->GetChild(".Y")->GetNumber() << "\n";
  std::cout << "OUT  7: " << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".SCALE")->GetNumber() << "\n";
  std::cout << "OUT  8: " << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".XY")->GetIntVec().at(0) << "\n";
  std::cout << "OUT  9:" << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".XY")->GetIntVec().at(1) << "\n";
  std::cout << "OUT 10: " << root->GetChild(".FASE0000")->GetChild(".MAP")->GetChild(".BITMAP")->GetString() << "\n";
  std::cout << "OUT 11:" << root->GetChild(".FASE0000")->GetChild(".XYZ")->GetIntVec().at(0) << "\n";
  std::cout << "OUT 12:" << root->GetChild(".FASE0000")->GetChild(".XYZ")->GetIntVec().at(1) << "\n";
  std::cout << "OUT 13:" << root->GetChild(".FASE0000")->GetChild(".XYZ")->GetIntVec().at(2) << "\n";
  std::cout << "OUT 14:" << root->GetChild(".FASE0000")->GetChild(".ARRAY")->GetNodeVec().at(0)->GetChild(".STR")->GetString() << "\n";
  std::cout << "OUT 15:" << root->GetChild(".FASE0000")->GetChild(".ARRAY")->GetNodeVec().at(1)->GetChild(".STR")->GetString() << "\n";
  std::cout << "OUT 16:" << root->GetChild(".FASE0000")->GetChild(".ARRAY")->GetNodeVec().at(2)->GetChild(".STR")->GetString() << "\n";
  std::cout << "OUT 17:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(0).at(0) << "\n";
  std::cout << "OUT 18:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(0).at(1) << "\n";
  std::cout << "OUT 19:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(0).at(2) << "\n";
  std::cout << "OUT 20:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(1).at(0) << "\n";
  std::cout << "OUT 21:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(1).at(1) << "\n";
  std::cout << "OUT 22:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(1).at(2) << "\n";
  std::cout << "OUT 23:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(2).at(0) << "\n";
  std::cout << "OUT 24:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(2).at(1) << "\n";
  std::cout << "OUT 25:" << root->GetChild(".FASE0000")->GetChild(".EXITPOINTS")->GetIntIntVec().at(2).at(2) << "\n";
}

bool MisFile::IsNumber(char c) const
{
  return c == '-' || (c >= '0' && c <= '9');
}

// TODO: rename. this is specific for array parsing
int MisFile::Peek()
{
  int n = 1;
  misFile.get(); // skip openning '['
  int c = misFile.peek();

  while (isspace(c))
  {
    misFile.get();
    c = misFile.peek();
    n++;
  }

  while (n >= 0)
  {
    misFile.unget();
    n--;
  }

  return c;
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
      ReadSpaces();

      if (IsNumber(misFile.peek()))
      {
        std::vector<int> intVec = ReadIntVec();
        Node *child = new Node();
        child->SetIntVec(intVec);
        node->SetChild(key, child);
      }
      else if (misFile.peek() == '[')
      {
        if (IsNumber(Peek()))
        {
          std::vector<std::vector<int>> intIntVec = ReadIntIntVec();
          Node *child = new Node();
          child->SetIntIntVec(intIntVec);
          node->SetChild(key, child);
        }
        else
        {
          std::vector<Node *> nodeVec = ReadNodeVec();
          Node *child = new Node();
          child->SetNodeVec(nodeVec);
          node->SetChild(key, child);
        }
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

std::vector<std::vector<int>> MisFile::ReadIntIntVec()
{
  std::vector<std::vector<int>> intIntVec;

  while (misFile.peek() != ']')
  {
    if (misFile.peek() == '[')
    {
      misFile.get();
      intIntVec.push_back(ReadIntVec());
    }
    else
    {
      misFile.get();
    }
  }

  misFile.get(); // consume ']'

  return intIntVec;
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
