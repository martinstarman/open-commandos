#include "utils.h"

int GetBufferValue(std::vector<char> buffer)
{
  int value = 0;

  for (int i = 0; i < buffer.size(); i++)
  {
    value |= (unsigned char)buffer.at(i) << i * 8;
  }

  return value;
}
