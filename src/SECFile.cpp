#include "SECFile.h"
#include <SDL.h>
#include "Sector.h"
#include <string>
#include "Utils.h"
#include <vector>

namespace GreenBeret
{
    SECFile::SECFile(const std::string &path)
        : block(BLOCK::VERTEX),
          points({})
    {
        SDL_Log("Opening SEC file: %s", path.c_str());
        file.open(path, std::ifstream::binary);
    }

    SECFile::~SECFile()
    {
        file.close();
    }

    void SECFile::Parse()
    {
        std::string line;

        while (std::getline(file, line))
        {
            line = trim(line);

            if (line != "")
            {
                if (block == BLOCK::VERTEX)
                {
                    int vertices_no = std::stoi(line);
                    SDL_Log("Number of vertices: %i", vertices_no);

                    for (int i = 0; i < vertices_no; i++)
                    {
                        std::getline(file, line);
                        auto values = split(line, ' ');
                        float x = std::stof(values.at(0));
                        float y = std::stof(values.at(1)) * sin40;
                        points.emplace_back(PointF(x, y));
                    }

                    block = BLOCK::SECTOR;
                }
                else if (block == BLOCK::SECTOR)
                {
                    int sectors_no = std::stoi(line);
                    SDL_Log("Number of sectors: %i", sectors_no);

                    for (int i = 0; i < sectors_no; i++)
                    {
                        // skip empty line
                        std::getline(file, line); // TODO: make it more robust

                        // number of vertices
                        std::getline(file, line);
                        auto values = split(line, ' ');
                        int vertices_no = std::stoi(values.at(0));
                        std::vector<PointF> sector_points;

                        // TODO: use remaining values on line (7 integers)

                        for (int j = 0; j < vertices_no; j++)
                        {
                            std::getline(file, line);
                            int vertex_pos = std::stoi(line);
                            sector_points.emplace_back(points.at(vertex_pos));
                        }

                        Sector sector(sector_points);
                        sectors.emplace_back(sector);
                        block = BLOCK::BRIDGE;
                    }
                }
                // TODO: parse all blocks
                else
                {
                    SDL_Log("Skipping SEC file line: %s", line.c_str());
                }
            }
        }
    }
} // namespace GreenBeret
