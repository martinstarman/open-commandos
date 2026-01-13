#include <string>
#include "mis-value.h"

MisValue::MisValue() = default;

MisValue::~MisValue()
{
  for (auto const &[key, misValue] : node)
  {
    delete misValue;
  }
}

void MisValue::SetString(const std::string &value)
{
  string = value;
  tag = MisValueTag::String;
}

std::string &MisValue::GetString()
{
  return string;
}

void MisValue::SetNumber(int value)
{
  number = value;
  tag = MisValueTag::Number;
}

int MisValue::GetNumber()
{
  return number;
}

void MisValue::SetMisValue(const std::string &key, MisValue *value)
{
  node.emplace(key, value);
  tag = MisValueTag::Node;
}

MisValue *MisValue::GetNode(const std::string &key)
{
  return node.at(key);
}
