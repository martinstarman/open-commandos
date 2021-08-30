#include "VOLFile.h"

#include "Tile.h"
#include "Utils.h"
#include "Vector2.h"

#include <fstream>
#include <SDL.h>
#include <string>

namespace GreenBeret
{
    VOLFile::VOLFile() = default;

    VOLFile::VOLFile(const std::string &path)
        : w(0),
          h(0),
          polygons({})
    {
        SDL_Log("Opening VOL file: %s", path.c_str());
        file.open(path, std::ifstream::binary);
    }

    VOLFile::~VOLFile()
    {
        file.close();
    }

    void VOLFile::Parse()
    {
        std::string line;

        while (std::getline(file, line))
        {
            line = trim(line);

            // remove comments
            int cpos = (int)line.find(";");
            if (cpos != std::string::npos)
            {
                line.erase(cpos, line.length());
            }

            // empty lines, comments, unimportant stuff
            if (line == "" ||
                line.find("{", 0) == 0 ||
                line.find("}", 0) == 0)
            {
                continue;
            }
            // map size
            else if (line.find("MAPDIMXY", 0) == 0)
            {
                int pos = (int)line.find("MAPDIMXY", 0);
                line.erase(pos, 8);

                auto values = split(line, ',');
                w = std::stoi(values[0]);
                h = std::stoi(values[1]);

                SDL_Log("Map size (WxH): %ix%i", w, h);
            }
            // polygon
            else if (line.find("POLY", 0) == 0)
            {
                int pos = (int)line.find("POLY", 0);
                line.erase(pos, 4);

                auto values = split(line, ',');
                std::string name = values[0]; // TODO: remove quotes?
                float x = std::stof(values[1]);
                float y = std::stof(values[2]) * sin40;
                int z = std::stoi(values[3]);
                int h = std::stoi(values[4]);
                // int vertexNo = std::stoi(values[5]);
                // int tileNo = std::stoi(values[6]);

                polygons.emplace_back(Polygon(name, x, y, z, h));
            }
            // polygon point
            else if (line.find("POINT", 0) == 0)
            {
                int pos = (int)line.find("POINT", 0);
                line.erase(pos, 5);

                auto values = split(line, ',');
                float x = std::stof(values[0]);
                float y = std::stof(values[1]) * sin40;

                // add to last polygon
                polygons.back().points.emplace_back(Vector2(x, y));
            }
            // polygon tile
            else if (line.find("TILE", 0) == 0)
            {
                int pos = (int)line.find("TILE", 0);
                line.erase(pos, 4);

                auto values = split(line, ',');
                float x = std::stof(values[0]);
                float y = std::stof(values[1]);
                float w = std::stof(values[2]);
                float h = std::stof(values[3]);
                float offsetX = std::stof(values[4]);
                float offsetY = std::stof(values[5]);
                int brightness = std::stoi(values[6]);
                std::string fileName = values[7];
                std::string transformation = values[8];

                fileName.erase(0, 1); // remove first "
                fileName.erase(fileName.size() - 1, 1); // remove last "

                transformation.erase(0, 1); // remove first "
                transformation.erase(transformation.size() - 1, 1); // remove last "
                transformation = trim(transformation);

                // add to last polygon
                polygons.back().tiles.emplace_back(Tile(x, y, w, h, offsetX, offsetY, brightness,
                                                        fileName, transformation));
            }
            else
            {
                SDL_Log("Skipping VOL file line: %s", line.c_str());
            }
        }
    }
} // namespace GreenBeret
