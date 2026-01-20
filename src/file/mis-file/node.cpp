#include <string>
#include "node.h"

Node::Node() = default;

Node::~Node()
{
  for (auto const &[key, child] : children)
  {
    delete child;
  }

  for (auto const node : nodeVec)
  {
    delete node;
  }
}

void Node::SetString(const std::string &value)
{
  string = value;
  tag = NodeTag::String;
}

const std::string &Node::GetString() const
{
  return string;
}

void Node::SetNumber(int value)
{
  number = value;
  tag = NodeTag::Number;
}

int Node::GetNumber() const
{
  return number;
}

void Node::SetChild(const std::string &key, Node *value)
{
  children.emplace(key, value);
  tag = NodeTag::Child;
}

Node *Node::GetChild(const std::string &key) const
{
  return children.at(key);
}

void Node::SetIntVec(std::vector<int> value)
{
  intVec = value;
  tag = NodeTag::IntVec;
}

std::vector<int> Node::GetIntVec() const
{
  return intVec;
}

void Node::SetIntIntVec(std::vector<std::vector<int>> value)
{
  intIntVec = value;
  tag = IntIntVec;
}

std::vector<std::vector<int>> Node::GetIntIntVec() const
{
  return intIntVec;
}

void Node::SetNodeVec(std::vector<Node *> value)
{
  nodeVec = value;
  tag = NodeTag::NodeVec;
}

std::vector<Node *> Node::GetNodeVec() const
{
  return nodeVec;
}
