#include <bits/stdc++.h>
#include "SDL_utils.h"
#include "SDL_image_basic.h"
#include "SDL_mixer_basic.h"
#include "SDL_ttf_basic.h"
#include "gameBoard.h"
#include "game.h"

using namespace std;

void Game::initializeGame()
{
    SDL_Texture* image = loadTexture("image/background.png", renderer);
    SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
    targetPoint = 10000;
    Move = 15;
    bool quit = true;
    while (quit)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if((e.button.x <= 510) && (e.button.x >= 320) && (e.button.y <= 460) && (e.button.y >= 380))
            {
                SDL_Texture* image = loadTexture("image/gameboard.png", renderer);
                SDL_RenderCopy(renderer, image, NULL, NULL);
                SDL_RenderPresent(renderer);
                SDL_Delay(10);
                quit = false;
            }
        }
    }
}

int Game::gamePlay()
{
    int playerMove = Move;
    int Point = 0;
    gameBoard game_board(renderer);
    game_board.fillBoard();
    bool isRunning = false;
    while (!isRunning)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            while(!game_board.checkPossibleMove())
            {
                //SDL_Delay(100);
                game_board.mixTile();
                game_board.renderBoard();
            }
            game_board.findTileSelected(e.button.x, e.button.y, playerMove);
            while(game_board.findMatch(Point))
            {
                game_board.dropTile(Point);
            }
            if(point >= targetPoint)
            {

            }
            else if(playerMove == 0)
            {

            }
        }
    }
}
