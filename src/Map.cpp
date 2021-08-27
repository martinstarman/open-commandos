#include "Map.h"
#include "PointF.h"
#include <SDL.h>
#include "SECFile.h"
#include "Utils.h"
#include "VOLFile.h"
#include "WADFile.h"
#include "Window.h"

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
        : offset_x(0),
          offset_y(0)
    {
    }

    Map::~Map()
    {
        delete instance;
        delete wad_file;
        delete vol_file;
        delete sec_file;
    }

    void Map::Load(const std::string &name)
    {
        vol_file = new VOLFile("DATOS/MISIONES/MAPA" + name + ".VOL");
        vol_file->Parse();

        wad_file = new WADFile("DATOS/RECURSOS/BMPS/MAP/FASE" + name + ".WAD");
        wad_file->Parse();

        sec_file = new SECFile("DATOS/MISIONES/MAPA" + name + ".SEC");
        sec_file->Parse();
    }

    void Map::Render()
    {
        for (const auto &tile : vol_file->tiles)
        {
            if (tile.sprite.at(0) != '-') // sprites starting with "minus" are invisible
            {
                SDL_Point pos = (SDL_Point)ToWindowPoint(PointF(tile.x, tile.y));
                SDL_Rect rect{pos.x, pos.y, tile.w, tile.h};

                if (tile.transformation == "")
                {
                    SDL_RenderCopy(Window::Get()->renderer, wad_file->GetImage(tile.sprite),
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

                    SDL_Point center{tile.x + tile.w / 2, tile.y + tile.h / 2};
                    SDL_RenderCopyEx(Window::Get()->renderer, wad_file->GetImage(tile.sprite),
                                     nullptr, &rect, 0, &center, flip);
                    // red
                    SDL_SetRenderDrawColor(Window::Get()->renderer, 255, 0, 0, 255);
                    SDL_RenderDrawRect(Window::Get()->renderer, &rect);
                }
            }
        }

        // pink
        SDL_SetRenderDrawColor(Window::Get()->renderer, 255, 51, 239, 255);

        // Hint for programmers:
        // In Commandos the player looks down at the map from an angle of 40 degrees. That means that the y-coordinates have to be multiplied by sin(40) to get the correct screen coordinates.
        for (const auto &polygon : vol_file->polygons)
        {
            // draw polygon center
            PointF pc = polygon.center;
            pc.y = pc.y * sin40deg;
            SDL_Point center = (SDL_Point)ToWindowPoint(pc);
            SDL_RenderDrawLine(Window::Get()->renderer, center.x - 5, center.y - 5, center.x + 5, center.y + 5);
            SDL_RenderDrawLine(Window::Get()->renderer, center.x + 5, center.y - 5, center.x - 5, center.y + 5);

            if (polygon.points.size() > 1)
            {
                for (int i = 0; i < polygon.points.size(); i++)
                {
                    PointF p1 = polygon.points.at(i);
                    PointF p2 = polygon.points.at((i + 1) % polygon.points.size());

                    PointF p5 = p1 + polygon.center;
                    p5.y = p5.y * sin40deg;

                    PointF p6 = p2 + polygon.center;
                    p6.y = p6.y * sin40deg;

                    // TODO: calculate correct position in VOL file
                    SDL_Point p3 = (SDL_Point)ToWindowPoint(p5);
                    SDL_Point p4 = (SDL_Point)ToWindowPoint(p6);

                    SDL_RenderDrawLine(Window::Get()->renderer, p3.x, p3.y, p4.x, p4.y);
                }
            }
        }

        // blue
        SDL_SetRenderDrawColor(Window::Get()->renderer, 51, 255, 239, 255);

        for (const auto &sector : sec_file->sectors)
        {
            if (sector.points.size() > 1)
            {
                for (int i = 0; i < sector.points.size(); i++)
                {
                    PointF p3 = sector.points.at(i);
                    PointF p4 = sector.points.at((i + 1) % sector.points.size());

                    p3.y = p3.y * sin40deg;
                    p4.y = p4.y * sin40deg;

                    SDL_Point p1 = (SDL_Point)ToWindowPoint(p3);
                    SDL_Point p2 = (SDL_Point)ToWindowPoint(p4);

                    SDL_RenderDrawLine(Window::Get()->renderer, p1.x, p1.y, p2.x, p2.y);
                }
            }
        }
    }

    void Map::Move(int x, int y)
    {
        offset_x += x;
        offset_y += y;

        /*
        if (offset_x < 0)
        {
            offset_x = 0;
        }
        if (offset_x > vol_file->w - Window::Get()->w)
        {
            offset_x = vol_file->w - Window::Get()->w;
        }
        if (offset_y < 0)
        {
            offset_y = 0;
        }
        if (offset_y > vol_file->h - Window::Get()->h)
        {
            offset_y = vol_file->h - Window::Get()->h;
        }
        */
    }
} // namespace GreenBeret
