#pragma once

#include <string>

enum MisValueTag
{
  String,
  Number,
};

class MisValue
{
public:
  MisValue();
  ~MisValue();
  void SetString(const std::string &value);
  const std::string &GetString();
  void SetNumber(int value);
  int GetNumber();

private:
  MisValueTag tag;
  std::string string;
  int number;
};
