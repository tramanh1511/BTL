#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <bits/stdc++.h>
#include "SDL_image_basic.h"
#include "SDL_mixer_basic.h"
#include "gameTile.h"
#include "SDL_Time.h"

using namespace std;

const int boardRow = 9;
const int boardCol = 9;
const int numOfTile = 6;

static int highScore = 0;
static int Level;


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
    void fillBoard(int Level);
    bool findMatch(int& countPoint);
    void explodeTile(int x, int y, int& Point);
    bool selectTile(int xmouse, int ymouse, int &Move);
    bool checkPossibleMove();
    void dropTile(int& Point, int Level);
    void mixTile();
    void Pause();
    void CountTime();
    bool checkTime();
    void loadTime();
    void loadHighScore();
};

#endif // GAMEBOARD_H
