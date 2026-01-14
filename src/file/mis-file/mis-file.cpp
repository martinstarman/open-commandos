#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include "mis-file.h"
#include "mis-value.h"

// temp
#include <iostream>

MisFile::MisFile(std::string path) : key("")
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

  std::cout << "DONE!" << "\n";

  std::cout << "OUT: " << root->GetNode(".FASE0000")->GetNode(".DATOSFICHEROSMISION")->GetNode(".VOLUMENES")->GetString() << "\n";
  std::cout << "OUT: " << root->GetNode(".FASE0000")->GetNode(".DATOSFICHEROSMISION")->GetNode(".INTROSCRIPT")->GetString() << "\n";
  std::cout << "OUT: " << root->GetNode(".FASE0000")->GetNode(".X")->GetNumber() << "\n";
  std::cout << "OUT: " << root->GetNode(".FASE0000")->GetNode(".TEST")->GetNode(".A")->GetString() << "\n";
  std::cout << "OUT: " << root->GetNode(".FASE0000")->GetNode(".TEST")->GetNode(".B")->GetString() << "\n";
  std::cout << "OUT: " << root->GetNode(".FASE0000")->GetNode(".Y")->GetNumber() << "\n";
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

MisValue *MisFile::ReadNode()
{
  MisValue *node = new MisValue();

  while (!misFile.eof())
  {
    std::cout << "BLA" << "\n";
    char c = misFile.peek();

    if (isspace(c))
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
        std::cout << "string:" << key << "\n";
        MisValue *misValue = new MisValue();
        misValue->SetString(string);
        node->SetMisValue(key, misValue);
        key = "";
      }
    }
    else if (c == '-' || (c >= '0' && c <= '9'))
    {
      int number = ReadNumber();
      std::cout << "number:" << number << "\n";
      MisValue *misValue = new MisValue();
      misValue->SetNumber(number);
      node->SetMisValue(key, misValue);
      key = "";
    }
    else if (c == '[')
    {
      std::string s = key;
      misFile.get();
      key = "";
      std::cout << "node:" << s << "\n";
      node->SetMisValue(s, ReadNode());
    }
    else if (c == ']')
    {
      misFile.get();
      std::cout << "RET 1\n";
      return node;
    }
    else
    {
      std::cout << "Unknown: " << misFile.get() << "\n";
    }
  }

  std::cout << "RET 2\n";
  return node;
}

// char MisFile::Peek()
// {
//   while (misFile.peek() == ' ')
//   {
//     misFile.get();
//   }
//   return misFile.peek();
// }
