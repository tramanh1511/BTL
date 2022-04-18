#ifndef GAME_H
#define GAME_H
#include "gameBoard.h"

using namespace std;

//class Button
//{
//private:
//    int x = 0, y = 0;
//    int w = 0, h = 0;
//public:
//    SDL_Renderer* renderer = NULL;
//    SDL_Rect buttonRect = {x, y, w, h};
//    Button() {};
//    Button(SDL_Renderer* _renderer, SDL_Rect rect) : renderer(_renderer), buttonRect(rect) {};
//    ~Button() {};
//    void render();
//};

class Game
{
private:
    SDL_Renderer* renderer = NULL;
    SDL_Event e;
    gameBoard game_board;
    int point = 0, targetPoint = 0, Move = 0;
public:
    Game(SDL_Renderer* _renderer, SDL_Event _e) : renderer(_renderer), e(_e) {};
    void initializeGame();
    int gamePlay();
    int result(bool res);
};


#endif // GAME_H
