#include "VOLFile.h"
#include <fstream>
#include <SDL.h>
#include <string>
#include "Tile.h"
#include "Utils.h"

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

            // empty lines, comments, unimportant stuff
            if (line == "" || line.find(";", 0) == 0 || line.find("{", 0) == 0 ||
                line.find("}", 0) == 0)
            {
                continue;
            }
            // map size
            // MAPDIMXY 1453,2450
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
            // POLY "ARBOL26",1400,3053,0,159,0,2;Nombre,CentroX,CentroY,CentroZ,Altura,#vertices,#Tiles
            else if (line.find("POLY", 0) == 0)
            {
                int pos = (int)line.find("POLY", 0);
                line.erase(pos, 4);

                pos = (int)line.find(";");
                if (pos != std::string::npos)
                {
                    line.erase(pos, line.length());
                }

                auto values = split(line, ',');
                std::string name = values[0];
                float x = std::stof(values[1]);
                float y = std::stof(values[2]);
                int z = std::stoi(values[3]);
                int h = std::stoi(values[4]);
                int vertices_no = std::stoi(values[5]);
                int tiles_no = std::stoi(values[6]);

                Polygon poly(name, x, y, z, h, vertices_no, tiles_no);
                polygons.emplace_back(poly);

                // TODO: parse points here!
            }
            // polygon point
            // POINT -23,-4 ;Coord. X, Coord. Y
            else if (line.find("POINT", 0) == 0)
            {
                int pos = (int)line.find("POINT", 0);
                line.erase(pos, 5);

                pos = (int)line.find(";");
                if (pos != std::string::npos)
                {
                    line.erase(pos, line.length());
                }

                auto values = split(line, ',');
                int x = std::stoi(values[0]);
                int y = std::stoi(values[1]);

                // added to last polygon
                polygons.at(polygons.size() - 1).points.emplace_back(PointF(x, y));
            }
            // tile
            // TILE 1394, -1, 60, 4, 0, 0, 0,"TERRENO.BMP","   "
            else if (line.find("TILE", 0) == 0)
            {
                int pos = (int)line.find("TILE", 0);
                line.erase(pos, 4);

                auto values = split(line, ',');
                int x = std::stoi(values[0]);
                int y = std::stoi(values[1]);
                int w = std::stoi(values[2]);
                int h = std::stoi(values[3]);
                int offset_x = std::stoi(values[4]);
                int offset_y = std::stoi(values[5]);
                int brightness = std::stoi(values[6]);
                std::string sprite = values[7];
                sprite.erase(0, 1);                 // remove first "
                sprite.erase(sprite.size() - 1, 1); // remove last "
                std::string transformation = values[8];
                transformation.erase(0, 1);                         // remove first "
                transformation.erase(transformation.size() - 1, 1); // remove last "
                transformation = trim(transformation);

                tiles.emplace_back(Tile(x, y, w, h, offset_x, offset_y, brightness, sprite,
                                        transformation));
            }
            else
            {
                SDL_Log("Skipping VOL file line: %s", line.c_str());
            }
        }
    }
} // namespace GreenBeret
