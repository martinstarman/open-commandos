#include "bracket_file.h"

BracketFile::BracketFile(const std::string &path)
    : root(new Node())
{
  Open(path);
}

BracketFile::~BracketFile()
{
  file.close();
  delete root;
}

void BracketFile::Parse()
{
  std::string keyword = ReadString();
  Node *value = ReadValue();
  root->SetNode(keyword, value);
}

Node *BracketFile::GetRoot()
{
  return root;
}

Node *BracketFile::ReadValue()
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
  else
  {
    TraceLog(LOG_INFO, ("    > Unknown character " + std::to_string(c)).c_str());
  }

  ReadWhiteSpaces();
  return node;
}

Node *BracketFile::ReadNode()
{
  ReadWhiteSpaces();
  Node *node = new Node();

  while (Peek() != ']')
  {
    if (IsOpeningBracket(Peek()))
    {
      // TODO: MAPA0009.MIS, MAPA0012.MIS, MAPA0018.MIS
      //       [ .ANGBARRIDO 60 .DEMORA 50 ] [ .ANGBARRIDO 60 .DEMORA 50 ]
      ReadUntil(']');
      ReadWhiteSpaces();
    }
    else if (IsString(Peek()))
    {
      std::string ability = ReadString();
      Node *value = ReadValue();
      node->SetAbility(ability, value);
    }
    else
    {
      std::string keyword = ReadString();
      Node *value = ReadValue();
      node->SetNode(keyword, value);
    }
  }

  ReadClosingBracket();
  return node;
}

double BracketFile::ReadNumber()
{
  std::string string = ReadString();
  return atof(string.c_str());
}

std::vector<double> BracketFile::ReadListOfNumbers()
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

std::vector<std::vector<double>> BracketFile::ReadListOfNumberLists()
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

std::vector<Node *> BracketFile::ReadListOfNodes()
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

void BracketFile::ReadClosingBracket()
{
  ReadWhiteSpaces();
  Get();
}

Node *BracketFile::ReadAbility()
{
  ReadWhiteSpaces();
  Node *node = ReadNode();
  ReadClosingBracket();
  return node;
}

std::vector<std::string> BracketFile::ReadListOfAbilities()
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
