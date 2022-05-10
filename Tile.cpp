#include <bits/stdc++.h>
#include <SDL.h>
#include "SDL_image_basic.h"
#include "SDL_mixer_basic.h"
#include "Tile.h"

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

void Tile::swapTile(Tile otherTile, SDL_Texture* moveText, int speed)
{
    SDL_Rect thisRect = tileRect;
    SDL_Rect otherRect = otherTile.tileRect;
    while(otherRect.x != tileRect.x)
    {
        if(moveText != NULL)
        {
            otherRect.x += 7;
            otherRect.x = min(otherRect.x, tileRect.x);
        }
        else if(otherTile.tileRect.x > tileRect.x)
        {
            otherRect.x -= 7;
            tileRect.x += 7;
        }
        else
        {
            otherRect.x += 7;
            tileRect.x -= 7;
        }
        if (moveText == NULL)
        {
            SDL_RenderCopy(renderer, texture, NULL, &thisRect);
            SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        }
        else
        {
            SDL_RenderCopy(renderer, moveText, NULL, &otherRect);
        }
        SDL_RenderPresent(renderer);
        otherTile.renderEmpty();
        renderEmpty();
    }

    while (otherRect.y != tileRect.y)
    {
        if(moveText != NULL)
        {
            otherRect.y += 7;
            otherRect.y = min(otherRect.y, tileRect.y);
        }
        else if( otherTile.tileRect.y > tileRect.y)
        {
            otherRect.y -= 7;
            thisRect.y += 7;
        }
        else
        {
            otherRect.y += 7;
            thisRect.y -= 7;
        }
        if (moveText == NULL)
        {
            SDL_RenderCopy(renderer, texture, NULL, &thisRect);
            SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        }
        else
        {
            SDL_RenderCopy(renderer, moveText, NULL, &otherRect);
        }
        SDL_RenderPresent(renderer);
        otherTile.renderEmpty();
        renderEmpty();
    }
}
