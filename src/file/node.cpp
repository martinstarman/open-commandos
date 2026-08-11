#include "node.h"

Node::Node() = default;

Node::~Node()
{
  for (auto const &[key, child] : children)
  {
    delete child;
  }

  for (auto const node : listOfNodes)
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

void Node::SetNumber(double value)
{
  number = value;
  tag = NodeTag::Number;
}

double Node::GetNumber() const
{
  return number;
}

void Node::SetNode(const std::string &key, Node *value)
{
  children.emplace(key, value);
  tag = NodeTag::Child;
}

Node *Node::GetNode(const std::string &key) const
{
  assert(tag == NodeTag::Child);
  return children.at(key);
}

void Node::SetListOfNumbers(std::vector<double> value)
{
  listOfNumbers = value;
  tag = NodeTag::ListOfNumbers;
}

std::vector<double> Node::GetListOfNumbers() const
{
  return listOfNumbers;
}

void Node::SetListOfNumberLists(std::vector<std::vector<double>> value)
{
  listOfNumberLists = value;
  tag = ListOfNumberLists;
}

std::vector<std::vector<double>> Node::GetListOfNumberLists() const
{
  return listOfNumberLists;
}

void Node::SetListOfNodes(std::vector<Node *> value)
{
  listOfNodes = value;
  tag = NodeTag::ListOfNodes;
}

std::vector<Node *> Node::GetListOfNodes() const
{
  return listOfNodes;
}

void Node::SetAbility(const std::string &key, Node *value)
{
  children.emplace(key, value);
  tag = NodeTag::Ability;
}

Node *Node::GetAbility(const std::string &key) const
{
  assert(tag == NodeTag::Ability);
  return children.at(key);
}

void Node::SetListOfAbilities(std::vector<std::string> value)
{
  listOfAbilities = value;
  tag = NodeTag::ListOfAbilities;
}

std::vector<std::string> Node::GetListOfAbilities() const
{
  return listOfAbilities;
}
