#pragma once

#include <cctype>
#include <fstream>
#include <raylib.h>
#include <string>
#include <vector>

#include "node.h"
#include "text_file.h"

class MisFile : public TextFile
{
public:
  MisFile(const std::string &path);
  ~MisFile();
  void Parse() override;
  Node *GetRoot();

private:
  Node *root;
  Node *ReadValue();
  Node *ReadNode();
  double ReadNumber(); // TODO: unify with TextFile
  std::vector<double> ReadListOfNumbers();
  std::vector<std::vector<double>> ReadListOfNumberLists();
  std::vector<Node *> ReadListOfNodes();
  Node *ReadAbility();
  std::vector<std::string> ReadListOfAbilities();
  void ReadClosingBracket();
};
