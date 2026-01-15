#include <string>
#include "node.h"

Node::Node() = default;

Node::~Node()
{
  for (auto const &[key, child] : children)
  {
    delete child;
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

void Node::SetVec2(std::tuple<int, int> value)
{
  vec2 = value;
  tag = NodeTag::Vec2;
}

std::tuple<int, int> Node::GetVec2() const
{
  return vec2;
}

void Node::SetVec3(std::tuple<int, int, int> value)
{
  vec3 = value;
  tag = NodeTag::Vec3;
}

std::tuple<int, int, int> Node::GetVec3() const
{
  return vec3;
}
