#pragma once

#include <map>
#include <string>
#include <vector>

enum NodeTag
{
  String,
  Number,
  Child,
  ListOfNumbers,
  ListOfNumberLists,
  ListOfNodes,
  Ability,
  ListOfAbilities,
};

class Node
{
public:
  Node();
  ~Node();
  void SetString(const std::string &value);
  const std::string &GetString() const;
  void SetNumber(double value);
  double GetNumber() const;
  void SetNode(const std::string &key, Node *value);
  Node *GetNode(const std::string &key) const;
  void SetListOfNumbers(std::vector<double> value);
  std::vector<double> GetListOfNumbers() const;
  void SetListOfNumberLists(std::vector<std::vector<double>> value);
  std::vector<std::vector<double>> GetListOfNumberLists() const;
  void SetListOfNodes(std::vector<Node *> value);
  std::vector<Node *> GetListOfNodes() const;
  void SetAbility(const std::string &key, Node *value);
  Node *GetAbility(const std::string &key) const;
  void SetListOfAbilities(std::vector<std::string> value);
  std::vector<std::string> GetListOfAbilities() const;

private:
  NodeTag tag;
  std::string string;
  int number;
  std::map<std::string, Node *> children;
  std::vector<double> listOfNumbers;
  std::vector<std::vector<double>> listOfNumberLists;
  std::vector<Node *> listOfNodes;
  std::vector<std::string> listOfAbilities;
};
