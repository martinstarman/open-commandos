#include "sector.h"

Sector::Sector(
    int numberOfVertices,
    const std::vector<int> &vertexIndexes,
    double x,
    double y,
    double z,
    int type,
    int height,
    int offset,
    int flags)
    : numberOfVertices(numberOfVertices),
      vertexIndexes(vertexIndexes),
      x(x),
      y(y),
      z(z),
      type(type),
      height(height),
      offset(offset),
      flags(flags)
{
}

Sector::~Sector() = default;
