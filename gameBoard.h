#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <bits/stdc++.h>
#include "SDL_image_basic.h"
#include "SDL_mixer_basic.h"
#include "gameTile.h"
#include "gameBoard.h"

using namespace std;

const int boardRow = 9;
const int boardCol = 9;
const int numOfTile = 6;


class gameBoard
{
private:
    SDL_Renderer* renderer = NULL;
    int hiddenPoint = 0;
public:
    Tile tileBoard[boardRow][boardCol];
    gameBoard() {};
    gameBoard(SDL_Renderer* _renderer) : renderer(_renderer) {};
    ~gameBoard() {};

    void renderBoard();
    void fillBoard();
    bool findMatch(int& countPoint);
    void explodeTile(int x, int y, int& Point);
    bool selectTile(int xmouse, int ymouse, int &Move);
    bool checkPossibleMove();
    void dropTile(int& Point);
    void mixTile();
};

#endif // GAMEBOARD_H
