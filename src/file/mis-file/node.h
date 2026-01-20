#pragma once

#include <map>
#include <string>
#include <vector>

enum NodeTag
{
  String,
  Number,
  Child,
  IntVec,
  IntIntVec,
  NodeVec,
};

class Node
{
public:
  Node();
  ~Node();
  void SetString(const std::string &value);
  const std::string &GetString() const;
  void SetNumber(int value);
  int GetNumber() const;
  void SetChild(const std::string &key, Node *value);
  Node *GetChild(const std::string &key) const;
  void SetIntVec(std::vector<int> value);
  std::vector<int> GetIntVec() const;
  void SetIntIntVec(std::vector<std::vector<int>> value);
  std::vector<std::vector<int>> GetIntIntVec() const;
  void SetNodeVec(std::vector<Node *> value);
  std::vector<Node *> GetNodeVec() const;

private:
  NodeTag tag;
  std::string string;
  int number;
  std::map<std::string, Node *> children;
  std::vector<int> intVec;
  std::vector<std::vector<int>> intIntVec;
  std::vector<Node *> nodeVec;
};
