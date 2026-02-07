#include "vol-file-node.h"

VolFileNode::VolFileNode() = default;

VolFileNode::~VolFileNode()
{
  for (auto const &[key, child] : children)
  {
    delete child;
  }
}

void VolFileNode::SetVolFileNode(const std::string &key, VolFileNode *value)
{
  children.emplace(key, value);
  tag = VolFileNodeTag::VolFileNodeTagChild;
}

VolFileNode *VolFileNode::GetVolFileNode(const std::string &key) const
{
  return children.at(key);
}

void VolFileNode::SetListOfNumbers(std::vector<int> value)
{
  listOfNumbers = value;
  tag = VolFileNodeTag::VolFileNodeTagListOfNumbers;
}

std::vector<int> VolFileNode::GetListOfNumbers() const
{
  return listOfNumbers;
}
