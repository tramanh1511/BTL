#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <bits/stdc++.h>
#include "SDL_image_basic.h"
#include "SDL_mixer_basic.h"
#include "Tile.h"

using namespace std;

const int boardRow = 8;
const int boardCol = 9;
const int numOfTile = 5;


class gameBoard
{
private:
    SDL_Renderer* renderer = NULL;
    int speed = 25;
    int hiddenPoint = 0;
public:
    Tile tileBoard[boardRow][boardCol];
    gameBoard() {};
    gameBoard(SDL_Renderer* _renderer) : renderer(_renderer) {};
    ~gameBoard() {};

    void renderBoard();
    void fillBoard();
    bool findMatch(int& countPoint);
    bool findTileSelected(int xmouse, int ymouse, int &Move);
    bool checkPossibleMove();
    void dropTile(int& Point);
    void mixTile();


};

#endif // GAMEBOARD_H
