#include "text-file.h"

TextFile::TextFile() : pointer(-1)
{
}

TextFile::~TextFile()
{
  file.close();
}

void TextFile::Open(const std::string &path)
{
  file.open(path);
  file.seekg(0, std::ios_base::end);
  std::streampos fileSize = file.tellg();
  buffer.resize(fileSize);
  file.seekg(0, std::ios_base::beg);
  file.read(&buffer[0], fileSize);
}

void TextFile::Parse()
{
}

char TextFile::Peek()
{
  return buffer.at(pointer + 1);
}

char TextFile::Get()
{
  return buffer.at(++pointer);
}

void TextFile::Unget()
{
  pointer--;
}

bool TextFile::IsNumber(char c) const
{
  return c == '-' || (c >= '0' && c <= '9');
}

bool TextFile::IsString(char c) const
{
  return c >= 'A' && c <= 'Z';
}

void TextFile::ReadUntil(char c)
{
  while (Peek() != c)
  {
    Get();
  }

  Get();
}

int TextFile::ReadWhiteSpaces()
{
  int i = 0;

  while (isspace(Peek()))
  {
    i++;
    Get();
  }

  return i;
}

double TextFile::ReadNumber()
{
  ReadWhiteSpaces();
  std::string string;

  while (IsNumber(Peek()))
  {
    string.push_back(Get());
  }

  return atof(string.c_str());
}

std::string TextFile::ReadString()
{
  ReadWhiteSpaces();
  std::string string;

  while (!isspace(Peek()))
  {
    string.push_back(Get());
  }

  return string;
}
