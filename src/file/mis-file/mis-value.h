#pragma once

#include <map>
#include <string>

enum MisValueTag
{
  String,
  Number,
  Node,
};

class MisValue
{
public:
  MisValue();
  ~MisValue();
  void SetString(const std::string &value);
  std::string &GetString();
  void SetNumber(int value);
  int GetNumber();
  void SetMisValue(const std::string &key, MisValue *value);
  MisValue* GetNode(const std::string &key);

private:
  MisValueTag tag;
  std::string string;
  int number;
  std::map<std::string, MisValue*> node;
};
