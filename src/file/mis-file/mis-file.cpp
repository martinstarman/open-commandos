#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include "mis-file.h"
#include "mis-value.h"

// temp
#include <iostream>

MisFile::MisFile(std::string path) : key(""), root(new MisValue())
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
  ReadNode(root);
  std::cout << "OUT: " << root->GetNode(".FASE0000")->GetNode(".DATOSFICHEROSMISION")->GetNode(".VOLUMENES")->GetString() << "\n";
  std::cout << "OUT: " << root->GetNode(".FASE0000")->GetNode(".DATOSFICHEROSMISION")->GetNode(".INTROSCRIPT")->GetString() << "\n";
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

void MisFile::ReadNode(MisValue *parent)
{
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
        MisValue *misValue = new MisValue();
        misValue->SetString(string);
        parent->SetMisValue(key, misValue);
        key = "";
      }
    }
    else if (c == '-' || (c >= '0' && c <= '9'))
    {
      int number = ReadNumber();
      MisValue *misValue = new MisValue();
      misValue->SetNumber(number);
      parent->SetMisValue(key, misValue);
      key = "";
    }
    else if (c == '[')
    {
      MisValue *misValue = new MisValue();
      parent->SetMisValue(key, misValue);
      key = "";
      misFile.get();
      ReadNode(misValue);
    }
    else if (c == ']')
    {
      misFile.get();
    }
    else
    {
      std::cout << "Unknown: " << misFile.get() << "\n";
    }
  }
}

// char MisFile::Peek()
// {
//   while (misFile.peek() == ' ')
//   {
//     misFile.get();
//   }
//   return misFile.peek();
// }
