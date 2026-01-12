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
}

void MisFile::Parse()
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
        MisValue misValue;
        misValue.SetString(string);
        parsed[key] = misValue;
        key = "";
      }
    }
    else if (c == '-' || (c >= '0' && c <= '9'))
    {
      int number = ReadNumber();

      MisValue misValue;
      misValue.SetNumber(number);
      parsed[key] = misValue;
      key = "";
    }
    else
    {
      std::cout << "Unknown: " << misFile.get() << "\n";
    }
  }

  std::cout << "OUT: " << parsed[".VOLUMENES"].GetString() << "\n";
  std::cout << "OUT: " << parsed[".X"].GetNumber() << "\n";
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

// char MisFile::Peek()
// {
//   while (misFile.peek() == ' ')
//   {
//     misFile.get();
//   }
//   return misFile.peek();
// }
