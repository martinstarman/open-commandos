#pragma once

#include <vector>

class Sector
{
public:
  Sector(int numberOfVertices,
         const std::vector<int> &vertexIndexes,
         double x,
         double y,
         double z,
         int type,
         int height,
         int offset,
         int flags);
  ~Sector();

private:
  int numberOfVertices;
  std::vector<int> vertexIndexes;
  double x;
  double y;
  double z;
  int type; // TODO: enum
  int height;
  int offset;
  int flags; // TODO: enum
};
