#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include <vector>
#include "mis-file.h"
#include "node.h"

MisFile::MisFile(const std::string &path) : misFile(path), root(new Node())
{
  TraceLog(LOG_INFO, ("FILE: Opening .mis file " + path).c_str());
}

MisFile::~MisFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .mis file");
  misFile.close();
  delete root;
}

void MisFile::Parse()
{
  std::string keyword = ReadKeyword();
  Node *value = ReadValue();
  root->SetNode(keyword, value);

  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".DATOSFICHEROSMISION")->GetNode(".VOLUMENES")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".DATOSFICHEROSMISION")->GetNode(".SECTORES")->GetString().c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".MAP")->GetNode(".SCALE")->GetNumber()).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".MAP")->GetNode(".XY")->GetListOfNumbers().at(0)).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".MAP")->GetNode(".XY")->GetListOfNumbers().at(1)).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".WATER")->GetNode(".ANGINC")->GetNumber()).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".EXITPOINTS")->GetListOfNumberLists().at(0).at(0)).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".EXITPOINTS")->GetListOfNumberLists().at(0).at(1)).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".EXITPOINTS")->GetListOfNumberLists().at(0).at(2)).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".EXITPOINTS")->GetListOfNumberLists().at(1).at(0)).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".EXITPOINTS")->GetListOfNumberLists().at(1).at(1)).c_str());
  // TraceLog(LOG_INFO, std::to_string(root->GetNode(".FASE0000")->GetNode(".EXITPOINTS")->GetListOfNumberLists().at(1).at(2)).c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".PATRULLAS")->GetNodeList().at(0)->GetNode(".NAME")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".PATRULLAS")->GetNodeList().at(1)->GetNode(".NAME")->GetString().c_str());
}

bool MisFile::IsOpeningBracket(int c) const
{
  return c == '[';
}

bool MisFile::IsString(int c) const
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool MisFile::IsNumber(int c) const
{
  return c == '-' || (c >= '0' && c <= '9');
}

int MisFile::ReadWhiteSpaces()
{
  int i = 0;

  while (isspace(misFile.peek()))
  {
    i++;
    misFile.get();
  }

  return i;
}

std::string MisFile::ReadKeyword()
{
  ReadWhiteSpaces();
  std::string keyword;

  while (!isspace(misFile.peek()))
  {
    keyword.push_back(misFile.get());
  }

  ReadWhiteSpaces();
  return keyword;
}

Node *MisFile::ReadValue()
{
  ReadWhiteSpaces();
  Node *node;
  int c = misFile.peek();

  if (IsOpeningBracket(c))
  {
    misFile.get();
    ReadWhiteSpaces();
    c = misFile.peek();

    if (IsNumber(c))
    {
      node = new Node();
      node->SetListOfNumbers(ReadListOfNumbers());
    }
    else if (IsOpeningBracket(c))
    {
      misFile.get();
      int whitespaces = ReadWhiteSpaces();
      int c = misFile.peek();

      for (int i = 0; i < whitespaces + 1; i++)
      {
        misFile.unget();
      }

      if (IsNumber(c))
      {
        node = new Node();
        node->SetListOfNumberLists(ReadListOfNumberLists());
      }
      else
      {
        node = new Node();
        node->SetNodeList(ReadNodeList());
      }
    }
    else
    {
      node = ReadNode();
    }
  }
  else if (IsNumber(c))
  {
    node = new Node();
    node->SetNumber(ReadNumber());
  }
  else if (IsString(c))
  {
    node = new Node();
    node->SetString(ReadString());
  }

  ReadWhiteSpaces();
  return node;
}

Node *MisFile::ReadNode()
{
  ReadWhiteSpaces();
  Node *node = new Node();

  while (misFile.peek() != ']')
  {
    std::string keyword = ReadKeyword();
    Node *value = ReadValue();
    node->SetNode(keyword, value);
  }

  ReadClosingBracket();
  ReadWhiteSpaces();
  return node;
}

std::string MisFile::ReadString()
{
  ReadWhiteSpaces();
  std::string string;

  while (!isspace(misFile.peek()))
  {
    string.push_back(misFile.get());
  }

  ReadWhiteSpaces();
  return string;
}

double MisFile::ReadNumber()
{
  std::string string = ReadString();
  return atof(string.c_str());
}

std::vector<double> MisFile::ReadListOfNumbers()
{
  ReadWhiteSpaces();
  std::vector<double> listOfNumbers;

  while (misFile.peek() != ']')
  {
    ReadWhiteSpaces();
    listOfNumbers.push_back(ReadNumber());
    ReadWhiteSpaces();
  }

  ReadClosingBracket();
  ReadWhiteSpaces();
  return listOfNumbers;
}

std::vector<std::vector<double>> MisFile::ReadListOfNumberLists()
{
  ReadWhiteSpaces();
  std::vector<std::vector<double>> listOfNumberLists;

  while (misFile.peek() != ']')
  {
    ReadWhiteSpaces();

    if (misFile.peek() == '[')
    {
      misFile.get();
      ReadWhiteSpaces();
      listOfNumberLists.push_back(ReadListOfNumbers());
      ReadWhiteSpaces();
    }

    ReadWhiteSpaces();
  }

  ReadClosingBracket();
  ReadWhiteSpaces();
  return listOfNumberLists;
}

std::vector<Node *> MisFile::ReadNodeList()
{
  ReadWhiteSpaces();
  std::vector<Node *> listOfNodes;

  while (misFile.peek() != ']')
  {
    ReadWhiteSpaces();

    if (misFile.peek() == '[')
    {
      misFile.get();
      ReadWhiteSpaces();
      listOfNodes.push_back(ReadNode());
      ReadWhiteSpaces();
    }

    ReadWhiteSpaces();
  }

  ReadClosingBracket();
  ReadWhiteSpaces();
  return listOfNodes;
}

void MisFile::ReadClosingBracket()
{
  misFile.get();
}
