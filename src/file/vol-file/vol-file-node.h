#pragma once

#include <map>
#include <string>
#include <vector>

enum VolFileNodeTag
{
  VolFileNodeTagChild,
  VolFileNodeTagListOfNumbers,
};

class VolFileNode
{
public:
  VolFileNode();
  ~VolFileNode();
  void SetVolFileNode(const std::string &key, VolFileNode *value);
  VolFileNode *GetVolFileNode(const std::string &key) const;
  void SetListOfNumbers(std::vector<int> value);
  std::vector<int> GetListOfNumbers() const;

private:
  VolFileNodeTag tag;
  std::map<std::string, VolFileNode *> children;
  std::vector<int> listOfNumbers;
};
