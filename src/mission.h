#pragma once

#include <algorithm>
#include <map>
#include <raylib.h>
#include <string>
#include <vector>

#include "globals.h"
#include "mis_file.h"
#include "polygon.h"
#include "sec_file.h"
#include "vol_file.h"
#include "wad_file.h"

class Mission
{
public:
  Mission();
  ~Mission();
  void Load(const std::string &name, const std::string &faseToken);
  void Update();
  void Render() const;
  void RenderDebug() const;
  int GetWidth() const;
  int GetHeight() const;

private:
  int width;
  int height;
  MisFile *misFile;
  VolFile *volFile;
  SecFile *secFile;
  WadFile *wadFile;
  int offsetX;
  int offsetY;
  std::vector<Polygon *> sortedPolygons;
  std::map<std::string, Texture *> textures;
  void SortPolygons();
};
