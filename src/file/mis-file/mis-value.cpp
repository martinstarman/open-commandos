#include <string>
#include "mis-value.h"

MisValue::MisValue() = default;

MisValue::~MisValue() = default;

void MisValue::SetString(const std::string &value)
{
  string = value;
  tag = MisValueTag::String;
}

const std::string &MisValue::GetString()
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
