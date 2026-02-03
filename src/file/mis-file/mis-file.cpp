#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include <vector>
#include "mis-file.h"
#include "node.h"

MisFile::MisFile(const std::string &path) : misFile(path), root(new Node()), pointer(-1)
{
  misFile.seekg(0, std::ios_base::end);
  std::streampos fileSize = misFile.tellg();
  buffer.resize(fileSize);
  misFile.seekg(0, std::ios_base::beg);
  misFile.read(&buffer[0], fileSize);

  TraceLog(LOG_INFO, ("FILE: Opening .mis file " + path).c_str());
}

MisFile::~MisFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .mis file");
  misFile.close();
  delete root;
}

int MisFile::Peek()
{
  return buffer.at(pointer + 1);
}

int MisFile::Get()
{
  return buffer.at(++pointer);
}

void MisFile::Unget()
{
  pointer--;
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
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".PATRULLAS")->GetListOfNodes().at(0)->GetNode(".NAME")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".PATRULLAS")->GetListOfNodes().at(1)->GetNode(".NAME")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".ACCIONES")->GetListOfNodes().at(0)->GetAbility("acMuerte")->GetNode(".CARISMA")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".ACCIONES")->GetListOfNodes().at(1)->GetAbility("acUsaHab")->GetNode(".CARISMA")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".LISTAS")->GetListOfAbilities().at(0).c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".LISTAS")->GetListOfAbilities().at(1).c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".LISTAS")->GetListOfAbilities().at(2).c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".LISTAS")->GetListOfAbilities().at(3).c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".ITWORKS")->GetAbility("ABCDA")->GetNode(".X")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".DOESNOTWORK")->GetAbility("ABCDB")->GetNode(".X")->GetString().c_str());
  //
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".INTERFACE")->GetNode(".INFOCARAS")->GetListOfNodes().at(0)->GetAbility("CARA")->GetNode(".TOKEN")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".INTERFACE")->GetNode(".INFOCARAS")->GetListOfNodes().at(1)->GetAbility("CARA")->GetNode(".TOKEN")->GetString().c_str());
  // TraceLog(LOG_INFO, root->GetNode(".FASE0000")->GetNode(".INTERFACE")->GetNode(".INFOCARAS")->GetListOfNodes().at(2)->GetAbility("CARA")->GetNode(".TOKEN")->GetString().c_str());
}

bool MisFile::IsOpeningBracket(char c) const
{
  return c == '[';
}

bool MisFile::IsString(char c) const
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool MisFile::IsNumber(char c) const
{
  return c == '-' || (c >= '0' && c <= '9');
}

int MisFile::ReadWhiteSpaces()
{
  int i = 0;

  while (isspace(Peek()))
  {
    i++;
    Get();
  }

  return i;
}

std::string MisFile::ReadKeyword()
{
  ReadWhiteSpaces();
  std::string keyword;

  while (!isspace(Peek()))
  {
    keyword.push_back(Get());
  }

  ReadWhiteSpaces();
  return keyword;
}

Node *MisFile::ReadValue()
{
  ReadWhiteSpaces();
  Node *node;
  char c = Peek();

  if (IsOpeningBracket(c))
  {
    Get();
    ReadWhiteSpaces();
    c = Peek();

    if (IsNumber(c))
    {
      node = new Node();
      node->SetListOfNumbers(ReadListOfNumbers());
    }
    else if (IsOpeningBracket(c))
    {
      Get();
      int whitespaces = ReadWhiteSpaces();
      char c = Peek();

      for (int i = 0; i < whitespaces + 1; i++)
      {
        Unget();
      }

      if (IsNumber(c))
      {
        node = new Node();
        node->SetListOfNumberLists(ReadListOfNumberLists());
      }
      else
      {
        node = new Node();
        node->SetListOfNodes(ReadListOfNodes());
      }
    }
    else if (IsString(c))
    {
      std::string abilityName = ReadString();
      int whitespaces = ReadWhiteSpaces();
      char c = Peek();

      if (IsOpeningBracket(c))
      {
        Get();
        node = new Node();
        node->SetAbility(abilityName, ReadAbility());
      }
      else
      {
        for (int i = 0; i < abilityName.size() + whitespaces; i++)
        {
          Unget();
        }

        node = new Node();
        node->SetListOfAbilities(ReadListOfAbilities());
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

  while (Peek() != ']')
  {
    if (IsString(Peek()))
    {
      std::string ability = ReadString();
      Node *value = ReadValue();
      node->SetAbility(ability, value);
    }
    else
    {
      std::string keyword = ReadKeyword();
      Node *value = ReadValue();
      node->SetNode(keyword, value);
    }
  }

  ReadClosingBracket();
  return node;
}

std::string MisFile::ReadString()
{
  ReadWhiteSpaces();
  std::string string;

  while (!isspace(Peek()))
  {
    string.push_back(Get());
  }

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

  while (Peek() != ']')
  {
    ReadWhiteSpaces();
    listOfNumbers.push_back(ReadNumber());
    ReadWhiteSpaces();
  }

  ReadClosingBracket();
  return listOfNumbers;
}

std::vector<std::vector<double>> MisFile::ReadListOfNumberLists()
{
  ReadWhiteSpaces();
  std::vector<std::vector<double>> listOfNumberLists;

  while (Peek() != ']')
  {
    ReadWhiteSpaces();

    if (Peek() == '[')
    {
      Get();
      ReadWhiteSpaces();
      listOfNumberLists.push_back(ReadListOfNumbers());
      ReadWhiteSpaces();
    }

    ReadWhiteSpaces();
  }

  ReadClosingBracket();
  return listOfNumberLists;
}

std::vector<Node *> MisFile::ReadListOfNodes()
{
  ReadWhiteSpaces();
  std::vector<Node *> listOfNodes;
  while (Peek() != ']')
  {
    ReadWhiteSpaces();

    if (Peek() == '[')
    {
      Get();
      listOfNodes.push_back(ReadNode());
    }
  }

  ReadClosingBracket();
  return listOfNodes;
}

void MisFile::ReadClosingBracket()
{
  ReadWhiteSpaces();
  Get();
}

Node *MisFile::ReadAbility()
{
  ReadWhiteSpaces();
  Node *node = ReadNode();
  ReadClosingBracket();
  return node;
}

std::vector<std::string> MisFile::ReadListOfAbilities()
{
  ReadWhiteSpaces();
  std::vector<std::string> listOfAbilities;

  while (Peek() != ']')
  {
    ReadWhiteSpaces();
    listOfAbilities.push_back(ReadString());
    ReadWhiteSpaces();
  }

  ReadClosingBracket();
  return listOfAbilities;
}
