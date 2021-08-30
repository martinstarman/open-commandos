#include "Map.h"

#include "SECFile.h"
#include "Utils.h"
#include "Vector2.h"
#include "VOLFile.h"
#include "WADFile.h"
#include "Window.h"

#include <algorithm>
#include <SDL.h>

namespace GreenBeret
{
    Map *Map::instance = nullptr;

    Map *Map::Get()
    {
        if (instance == nullptr)
        {
            instance = new Map();
        }
        return instance;
    }

    Map::Map()
        : offset(0.0f, 0.0f)
    {
    }

    Map::~Map()
    {
        delete instance;
        delete wadFile;
        delete volFile;
        delete secFile;
    }

    void Map::Load(const std::string &name)
    {
        volFile = new VOLFile("DATOS/MISIONES/MAPA" + name + ".VOL");
        volFile->Parse();

        // sort polygons by z index
        std::sort(volFile->polygons.begin(), volFile->polygons.end(),
                  [](Polygon a, Polygon b) -> bool
                  { return a.z < b.z; });

        wadFile = new WADFile("DATOS/RECURSOS/BMPS/MAP/FASE" + name + ".WAD");
        wadFile->Parse();

        secFile = new SECFile("DATOS/MISIONES/MAPA" + name + ".SEC");
        secFile->Parse();
    }

    void Map::Render()
    {
        for (const auto &polygon : volFile->polygons)
        {
            // pink
            SDL_SetRenderDrawColor(Window::Get()->renderer, 255, 51, 239, 255);

            // draw polygon center
            SDL_Point center = (SDL_Point)(polygon.center - Map::Get()->offset);
            SDL_RenderDrawLine(Window::Get()->renderer, center.x - 5, center.y - 5, center.x + 5,
                               center.y + 5);
            SDL_RenderDrawLine(Window::Get()->renderer, center.x + 5, center.y - 5, center.x - 5,
                               center.y + 5);

            // draw polygon
            if (polygon.points.size() > 1)
            {
                for (int i = 0; i < polygon.points.size(); i++)
                {
                    Vector2 p1 = polygon.points.at(i);
                    Vector2 p2 = polygon.points.at((i + 1) % polygon.points.size());

                    // TODO: move center to VOLFile.cpp?
                    SDL_Point p3 = (SDL_Point)(p1 + polygon.center - Map::Get()->offset);
                    SDL_Point p4 = (SDL_Point)(p2 + polygon.center - Map::Get()->offset);

                    SDL_RenderDrawLine(Window::Get()->renderer, p3.x, p3.y, p4.x, p4.y);
                }
            }

            // draw tiles
            for (const auto &tile : polygon.tiles)
            {
                if (tile.fileName.at(0) != '-') // sprites starting with "minus" are invisible
                {
                    SDL_Point pos = (SDL_Point)(tile.position - Map::Get()->offset);
                    SDL_Rect rect{pos.x, pos.y, (int)tile.size.x, (int)tile.size.y};

                    if (tile.transformation == "")
                    {
                        SDL_RenderCopy(Window::Get()->renderer, wadFile->GetImage(tile.fileName),
                                       nullptr, &rect);
                    }
                    else
                    {
                        SDL_RendererFlip flip;

                        if (tile.transformation == "X")
                        {
                            flip = SDL_FLIP_HORIZONTAL;
                        }
                        else if (tile.transformation == "Y")
                        {
                            flip = SDL_FLIP_VERTICAL;
                        }
                        else
                        {
                            flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL |
                                                                 SDL_FLIP_VERTICAL);
                        }

                        SDL_Point center{(int)tile.position.x + (int)(tile.size.x / 2),
                                         (int)tile.position.y + (int)(tile.size.y / 2)};
                        SDL_RenderCopyEx(Window::Get()->renderer, wadFile->GetImage(tile.fileName),
                                         nullptr, &rect, 0, &center, flip);
                    }

                    // red
                    // draw tile rectangle
                    //SDL_SetRenderDrawColor(Window::Get()->renderer, 255, 0, 0, 255);
                    //SDL_RenderDrawRect(Window::Get()->renderer, &rect);
                }
            }
        }

        // blue
        SDL_SetRenderDrawColor(Window::Get()->renderer, 51, 255, 239, 255);

        // draw sectors
        for (const auto &sector : secFile->sectors)
        {
            if (sector.points.size() > 1)
            {
                for (int i = 0; i < sector.points.size(); i++)
                {
                    Vector2 p1 = sector.points.at(i);
                    Vector2 p2 = sector.points.at((i + 1) % sector.points.size());

                    SDL_Point p3 = (SDL_Point)(p1 - Map::Get()->offset);
                    SDL_Point p4 = (SDL_Point)(p2 - Map::Get()->offset);

                    SDL_RenderDrawLine(Window::Get()->renderer, p3.x, p3.y, p4.x, p4.y);
                }
            }
        }
    }

    void Map::Move(int x, int y)
    {
        offset.x += x;
        offset.y += y;

        /*
        if (offset.x < 0)
        {
            offset.x = 0;
        }
        if (offset.x > volFile->w - Window::Get()->w)
        {
            offset.x = volFile->w - Window::Get()->w;
        }
        if (offset.y < 0)
        {
            offset.y = 0;
        }
        if (offset.y > volFile->h - Window::Get()->h)
        {
            offset.y = volFile->h - Window::Get()->h;
        }
        */
    }
} // namespace GreenBeret
