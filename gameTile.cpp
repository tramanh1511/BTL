#include <bits/stdc++.h>
#include <SDL.h>
#include "SDL_image_basic.h"
#include "SDL_mixer_basic.h"
#include "gameTile.h"

using namespace std;

void Tile::render()
{
    SDL_Texture* image = NULL;
    switch (type)
    {
    case 1:
        tile_status = tileStatus::Blue;
        image = loadTexture("image/blue.png", renderer);
        break;
    case 2:
        tile_status = tileStatus::Red;
        image = loadTexture("image/red.png", renderer);
        break;
    case 3:
        tile_status = tileStatus::Yellow;
        image = loadTexture("image/yellow.png", renderer);
        break;
    case 4:
        tile_status = tileStatus::Green;
        image = loadTexture("image/green.png", renderer);
        break;
    case 5:
        tile_status = tileStatus::Orange;
        image = loadTexture("image/orange.png", renderer);
        break;
    default:
        break;
    }
    SDL_RenderCopy(renderer, image, NULL, &tileRect);
    SDL_RenderPresent(renderer);
}

void Tile::renderSelected()
{
    SDL_Texture* image = loadTexture("image/selected.png", renderer);
    SDL_RenderCopy(renderer, image, NULL, &tileRect);
    SDL_RenderPresent(renderer);
}

void Tile::renderEmpty()
{
    SDL_Texture* image = loadTexture("image/empty.png", renderer);
    SDL_RenderCopy(renderer, image, NULL, &tileRect);
    SDL_RenderPresent(renderer);
}

void Tile::swapTile(Tile otherTile)
{
    SDL_Rect thisRect = tileRect;
    SDL_Rect otherRect = otherTile.tileRect;
    while(otherRect.y != tileRect.y)
    {
        if (otherTile.tileRect.y > tileRect.y)
        {
            otherRect.y -= 9;
            thisRect.y += 9;
        }
        else
        {
            otherRect.y += 9;
            thisRect.y -= 9;
        }
        otherTile.renderEmpty();
        renderEmpty();
        SDL_RenderCopy(renderer, texture, NULL, &thisRect);
        SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        SDL_RenderPresent(renderer);
    }
    while(otherRect.x != tileRect.x)
    {
        if (otherTile.tileRect.x > tileRect.x)
        {
            otherRect.x -= 9;
            thisRect.x += 9;
        }
        else
        {
            otherRect.x += 9;
            thisRect.x -= 9;
        }
        otherTile.renderEmpty();
        renderEmpty();
        SDL_RenderCopy(renderer, texture, NULL, &thisRect);
        SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        SDL_RenderPresent(renderer);
    }
}
