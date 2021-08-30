#include "SECFile.h"

#include "Sector.h"
#include "Utils.h"

#include <SDL.h>
#include <string>
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
                    int vertexNo = std::stoi(line);
                    SDL_Log("Number of vertices: %i", vertexNo);

                    for (int i = 0; i < vertexNo; i++)
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
                    int sectorNo = std::stoi(line);
                    SDL_Log("Number of sectors: %i", sectorNo);

                    for (int i = 0; i < sectorNo; i++)
                    {
                        // skip empty line
                        std::getline(file, line); // TODO: make it more robust

                        // number of vertices
                        std::getline(file, line);
                        auto values = split(line, ' ');
                        int vertexNo = std::stoi(values.at(0));
                        std::vector<PointF> sectorPoints;

                        // TODO: use remaining values on line (7 integers)

                        for (int j = 0; j < vertexNo; j++)
                        {
                            std::getline(file, line);
                            int vertexPos = std::stoi(line);
                            sectorPoints.emplace_back(points.at(vertexPos));
                        }

                        Sector sector(sectorPoints);
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
