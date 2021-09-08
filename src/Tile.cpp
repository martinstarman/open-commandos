#include "Tile.h"
#include "Window.h"

#include <SDL.h>
#include <vector>

namespace GreenBeret
{
    Tile::Tile(float x, float y, float w, float h, float shiftX, float shiftY, int brightness,
               const std::string &fileName, const std::string &transformation)
        : position(x, y),
          size(w, h),
          shift(shiftX, shiftY),
          brightness(brightness),
          fileName(fileName),
          transformation(transformation)
    {
        texture = SDL_CreateTexture(Window::Get()->renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, (int)w, (int)h);

        while (shift.x < 0)
        {
            shift.x += size.x;
        }

        while (shift.x >= size.x)
        {
            shift.x -= size.x;
        }

        while (shift.y < 0)
        {
            shift.y += size.y;
        }

        while (shift.y >= size.y)
        {
            shift.y -= size.y;
        }
    }

    Tile::~Tile()
    {
        SDL_DestroyTexture(texture);
    }

    void Tile::CreateTexture(SDL_Texture *originalTexture)
    {
        SDL_SetRenderTarget(Window::Get()->renderer, texture);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

        int w, h;
        SDL_QueryTexture(originalTexture, nullptr, nullptr, &w, &h);

        if (size.x <= w && size.y <= h) // tile is smaller or same size than original texture
        {
            SDL_Rect sourceTextureRect{0, 0, (int)size.x, (int)size.y};
            SDL_Rect targetTextureRect{0, 0, (int)size.x, (int)size.y};
            SDL_RenderCopy(Window::Get()->renderer, originalTexture, &sourceTextureRect,
                           &targetTextureRect);
        }
        else // tile is bigger than original texture
        {
            // repeat texture in both axis
            for (int x = 0; x <= size.x; x += w)
            {
                for (int y = 0; y <= size.y; y += h)
                {
                    SDL_Rect targetTextureRect{x, y, w, h};
                    SDL_RenderCopy(Window::Get()->renderer, originalTexture, nullptr,
                                   &targetTextureRect);
                }
            }
            SDL_RenderPresent(Window::Get()->renderer);
        }

        // tranform texture
        if (transformation != "")
        {
            SDL_RendererFlip flip;

            if (transformation == "X")
            {
                flip = SDL_FLIP_HORIZONTAL;
            }
            else if (transformation == "Y")
            {
                flip = SDL_FLIP_VERTICAL;
            }
            else
            {
                flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL |
                                                     SDL_FLIP_VERTICAL);
            }

            SDL_Point center{(int)(size.x / 2), (int)(size.y / 2)};
            SDL_Rect rect{0, 0, (int)size.x, (int)size.y};
            SDL_RenderCopyEx(Window::Get()->renderer, texture, nullptr, &rect, 0, &center, flip);
        }

        // TODO
        if (false && shift.x > 0) // left shift
        {
            // split texture into 2 vertical parts - left and right
            // and then swap those parts

            int y = (int)size.y;       // height is always tile height
            int lw = (int)shift.x;     // left part width
            int rw = (int)size.x - lw; // right part width

            // left texture
            SDL_Texture *lt = SDL_CreateTexture(Window::Get()->renderer, SDL_PIXELFORMAT_RGBA8888,
                                                SDL_TEXTUREACCESS_TARGET, lw, y);
            SDL_SetRenderTarget(Window::Get()->renderer, lt);
            SDL_SetTextureBlendMode(lt, SDL_BLENDMODE_BLEND);
            SDL_Rect leftSourceTextureRect{0, 0, lw, y};
            SDL_RenderCopy(Window::Get()->renderer, texture, &leftSourceTextureRect, nullptr);
            SDL_RenderPresent(Window::Get()->renderer);

            // right texture
            SDL_Texture *rt = SDL_CreateTexture(Window::Get()->renderer, SDL_PIXELFORMAT_RGBA8888,
                                                SDL_TEXTUREACCESS_TARGET, rw, y);
            SDL_SetRenderTarget(Window::Get()->renderer, rt);
            SDL_SetTextureBlendMode(rt, SDL_BLENDMODE_BLEND);
            SDL_Rect rightSourceTextureRect{lw, 0, rw, y};
            SDL_RenderCopy(Window::Get()->renderer, texture, &rightSourceTextureRect, nullptr);
            SDL_RenderPresent(Window::Get()->renderer);

            SDL_SetRenderTarget(Window::Get()->renderer, texture);
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
            SDL_Rect leftTargetTextureRect{0, 0, rw, y};
            SDL_Rect rightTargetTextureRect{rw, 0, lw, y};
            // render right texture to the left
            SDL_RenderCopy(Window::Get()->renderer, rt, nullptr, &leftTargetTextureRect);
            // render left texture to the right
            SDL_RenderCopy(Window::Get()->renderer, lt, nullptr, &rightTargetTextureRect);
            SDL_RenderPresent(Window::Get()->renderer);
        }

        // TODO
        if (false && shift.y > 0) // up shift
        {
            // split texture into 2 horizontal parts - top and bottom
            // and then swap those parts

            int x = (int)size.x;       // width is always tile width
            int th = (int)shift.y;     // top part height
            int bh = (int)size.y - th; // bottom part height

            // top texture
            SDL_Texture *tt = SDL_CreateTexture(Window::Get()->renderer, SDL_PIXELFORMAT_RGBA8888,
                                                SDL_TEXTUREACCESS_TARGET, x, th);
            SDL_SetRenderTarget(Window::Get()->renderer, tt);
            SDL_SetTextureBlendMode(tt, SDL_BLENDMODE_BLEND);
            SDL_Rect topSourceTextureRect{0, 0, x, th};
            SDL_RenderCopy(Window::Get()->renderer, texture, &topSourceTextureRect, nullptr);
            SDL_RenderPresent(Window::Get()->renderer);

            // bottom texture
            SDL_Texture *bt = SDL_CreateTexture(Window::Get()->renderer, SDL_PIXELFORMAT_RGBA8888,
                                                SDL_TEXTUREACCESS_TARGET, x, bh);
            SDL_SetRenderTarget(Window::Get()->renderer, bt);
            SDL_SetTextureBlendMode(bt, SDL_BLENDMODE_BLEND);
            SDL_Rect bottomSourceTextureRect{0, th, x, bh};
            SDL_RenderCopy(Window::Get()->renderer, texture, &bottomSourceTextureRect, nullptr);
            SDL_RenderPresent(Window::Get()->renderer);

            SDL_SetRenderTarget(Window::Get()->renderer, texture);
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
            SDL_Rect topTargetTextureRect{0, 0, x, bh};
            SDL_Rect bottomTargetTextureRect{0, bh, x, th};
            // render bottom texture to the top
            SDL_RenderCopy(Window::Get()->renderer, bt, nullptr, &topTargetTextureRect);
            // render top texture to the bottom
            SDL_RenderCopy(Window::Get()->renderer, tt, nullptr, &bottomTargetTextureRect);
            SDL_RenderPresent(Window::Get()->renderer);
        }

        // set renderer target to window
        SDL_SetRenderTarget(Window::Get()->renderer, nullptr);
    }
} // namespace GreenBeret
