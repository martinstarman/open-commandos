#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include <vector>
#include "mis-file.h"
#include "node.h"

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
  // TODO: MAPA0004.MIS
  // TraceLog(LOG_INFO, root->GetChild(".WATER")->GetChild(".BMP")->GetString().c_str());
}

bool MisFile::IsNumber(char c) const
{
  return c == '-' || (c >= '0' && c <= '9');
}

bool MisFile::IsString(char c) const
{
  return c == '.' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int MisFile::VecTypePeek()
{
  misFile.get(); // skip openning '['
  int c = misFile.peek();
  int offset = 1;

  while (isspace(c))
  {
    misFile.get();
    c = misFile.peek();
    offset++;
  }

  while (offset >= 0)
  {
    misFile.unget();
    offset--;
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
  std::string key;

  while (!misFile.eof())
  {
    char c = misFile.peek();

    if (isspace(c) || c == EOF)
    {
      misFile.get();
    }
    else if (IsString(c))
    {
      std::string string = ReadString();

      if (key.empty())
      {
        key = string;
      }
      else
      {
        Node *child = new Node();
        child->SetString(string);
        node->SetChild(key, child);
        key.clear();
      }
    }
    else if (IsNumber(c)) // TODO: handle decimal numbers (.SCALE)
    {
      int number = ReadNumber();
      Node *child = new Node();
      child->SetNumber(number);
      node->SetChild(key, child);
      key.clear();
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
        if (IsNumber(VecTypePeek()))
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

      key.clear();
    }
    else if (c == ']')
    {
      misFile.get();
      break;
    }
    else
    {
      TraceLog(LOG_WARNING, "Unknown character: " + c);
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

  // TODO: remove eof
  while (misFile.peek() != ']' && !misFile.eof())
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
