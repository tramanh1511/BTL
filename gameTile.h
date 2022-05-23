#ifndef GAMETILE_H
#define GAMETILE_H
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

enum tileStatus
{
    Empty,
    Selected,
    Blue,
    Green,
    Orange,
    Red,
    Yellow,
    Purple,
};

enum tileDouble
{
    Double,
    Single,
    Bomb
};

class Tile
{
private:
    int x = 0, y = 0;
    int w = 63, h = 63;
public:
    int type = 0, status = 0;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    SDL_Rect tileRect = {x, y, w, h};
    tileStatus tile_status = tileStatus::Empty;
    tileDouble tile_double = tileDouble::Single;
    Tile() {};
    ~Tile() {};
    void render();
    void renderSelected();
    void renderEmpty();
    void renderDouble();
    void swapTile(Tile otherTile);
};

#endif // GAMETILE_H
