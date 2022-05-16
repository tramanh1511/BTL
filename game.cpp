#include <bits/stdc++.h>
#include "SDL_utils.h"
#include "SDL_image_basic.h"
#include "SDL_mixer_basic.h"
#include "SDL_ttf_basic.h"
#include "gameBoard.h"
#include "game.h"

using namespace std;

SDL_Rect TargetScore = {50, 125, 120, 50};
SDL_Rect yourScore = {45, 310, 120, 50};
SDL_Rect MoveRect = { 70, 440, 60, 50};

void Game::initializeGame()
{
    if (!loadMusic()) cerr << "Failed to load music!\n";
    Mix_VolumeChunk(eatableSound, 32);
    Mix_VolumeChunk(selectedSound, 36);
    Mix_VolumeMusic(16);
    SDL_Texture* image = loadTexture("image/background.png", renderer);
    SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
    Mix_PlayMusic(backgroundMusic, -1);
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
    int yourMove = Move;
    int Point = 0;
    gameBoard game_board(renderer);
    loadFont("00000", renderer, yourScore);
    loadFont("10000", renderer, TargetScore);
    loadFont("20", renderer, MoveRect);
    game_board.fillBoard();

    bool isRunning = false;
    while (!isRunning)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            while(!game_board.checkPossibleMove())
            {
                SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
                SDL_RenderFillRect(renderer, &yourScore);
                loadFont("No Possible move!", renderer, yourScore);
                SDL_Delay(100);
                SDL_RenderFillRect(renderer, &yourScore);
                loadFont("Mix Tiles!", renderer, yourScore);
                game_board.mixTile();
                game_board.renderBoard();
            }

            game_board.findTileSelected(e.button.x, e.button.y, yourMove);
            while(game_board.findMatch(Point))
            {
                SDL_SetRenderDrawColor(renderer, 255, 170, 200, 0);
                SDL_RenderFillRect(renderer, &MoveRect);
                string tempMove = to_string(yourMove);
                const char* playerMove = tempMove.c_str();
                loadFont(playerMove, renderer, MoveRect);
                game_board.dropTile(Point);
            }
            if(point >= targetPoint)
            {


            }
            else if(yourMove == 0)
            {

            }
        }
    }
}
