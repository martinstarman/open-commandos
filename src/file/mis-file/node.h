#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>

enum NodeTag
{
  String,
  Number,
  Child,
  Vec2,
  Vec3,
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
  void SetVec2(std::tuple<int, int> value);
  std::tuple<int, int> GetVec2() const;
  void SetVec3(std::tuple<int, int, int> value);
  std::tuple<int, int, int> GetVec3() const;
  void SetNodeVec(std::vector<Node *> value);
  std::vector<Node *> GetNodeVec() const;

private:
  NodeTag tag;
  std::string string;
  int number;
  std::map<std::string, Node *> children;
  std::tuple<int, int> vec2;
  std::tuple<int, int, int> vec3;
  std::vector<Node *> nodeVec;
};
