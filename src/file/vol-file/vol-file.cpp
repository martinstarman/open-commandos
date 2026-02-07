#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include <vector>
#include "vol-file.h"
#include "vol-file-node.h"

VolFile::VolFile(const std::string &path) : volFile(path), pointer(-1)
{
  volFile.seekg(0, std::ios_base::end);
  std::streampos fileSize = volFile.tellg();
  buffer.resize(fileSize);
  volFile.seekg(0, std::ios_base::beg);
  volFile.read(&buffer[0], fileSize);

  TraceLog(LOG_INFO, ("FILE: Opening .vol file " + path).c_str());
}

VolFile::~VolFile()
{
  TraceLog(LOG_INFO, "    > Done, closing .vol file");
  volFile.close();
  delete root;
}

char VolFile::Peek()
{
  return buffer.at(pointer + 1);
}

char VolFile::Get()
{
  return buffer.at(++pointer);
}

void VolFile::Unget()
{
  pointer--;
}

void VolFile::Parse()
{
  ReadUntil('\n'); // read first line
  root = ReadNode();
  TraceLog(LOG_INFO, std::to_string(root->GetVolFileNode("MAPDIMXY")->GetListOfNumbers().at(0)).c_str());
  TraceLog(LOG_INFO, std::to_string(root->GetVolFileNode("MAPDIMXY")->GetListOfNumbers().at(1)).c_str());
}

bool VolFile::IsClosingBracket(char c) const
{
  return c == '}';
}

bool VolFile::IsString(char c) const
{
  return c >= 'A' && c <= 'Z';
}

bool VolFile::IsSemicolon(char c) const
{
  return c == ';';
}

bool VolFile::IsNumber(char c) const
{
  return c >= '0' && c <= '9';
}

int VolFile::ReadWhiteSpaces()
{
  int i = 0;

  while (isspace(Peek()))
  {
    i++;
    Get();
  }

  return i;
}

void VolFile::ReadUntil(char c)
{
  while (Peek() != c)
  {
    Get();
  }

  Get();
}

VolFileNode *VolFile::ReadNode()
{
  VolFileNode *node = new VolFileNode();

  while (!IsClosingBracket(Peek()))
  {
    ReadWhiteSpaces();

    if (IsSemicolon(Peek()))
    {
      ReadUntil('\n');
    }
    else if (IsString(Peek()))
    {
      std::string keyword = ReadKeyword();
      ReadWhiteSpaces();

      if (keyword == "MAPDIMXY")
      {
        VolFileNode *value = new VolFileNode();
        ReadWhiteSpaces();
        int x = ReadNumber();
        ReadWhiteSpaces();
        Get(); // read ','
        ReadWhiteSpaces();
        int y = ReadNumber();
        ReadWhiteSpaces();
        std::vector<int> listOfNumbers{x, y};
        value->SetListOfNumbers(listOfNumbers);
        node->SetVolFileNode(keyword, value);
      }
    }
  }

  return node;
}

std::string VolFile::ReadKeyword()
{
  ReadWhiteSpaces();
  std::string string;

  while (!isspace(Peek()))
  {
    string.push_back(Get());
  }

  return string;
}

int VolFile::ReadNumber()
{
  ReadWhiteSpaces();
  std::string string;

  while (IsNumber(Peek()))
  {
    string.push_back(Get());
  }

  return atoi(string.c_str());
}
