#ifndef GAME_H
#define GAME_H
#include "gameBoard.h"

using namespace std;

class Game
{
private:
    SDL_Renderer* renderer = NULL;
    SDL_Event e;
    gameBoard game_board;
    int point = 0, targetPoint = 0, Move = 0, Level = 0;
public:
    Game(SDL_Renderer* _renderer, SDL_Event _e) : renderer(_renderer), e(_e) {};
    void gameInitialize();
    void gameLevel();
    int gamePlay();
    int gameResult(int res);
    bool gamePlayAgain();
};


#endif // GAME_H
