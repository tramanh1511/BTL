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
SDL_Rect MoveRect = {70, 440, 60, 50};
SDL_Rect soundRect = {730, 10, 50, 50};
SDL_Rect playbutton = {280, 400, 180, 60};
SDL_Rect title = {400, 300, 300, 250};

void Game::gameInitialize()
{
    if (!loadMusic()) cerr << "Failed to load music!\n";
    Mix_VolumeChunk(eatableSound, 15);
    Mix_VolumeChunk(selectedSound, 15);
    Mix_VolumeMusic(80);
    SDL_Texture* image = loadTexture("image/background.png", renderer);
    SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
    Mix_PlayMusic(backgroundMusic, -1);
    bool isRunning = true;
    while (isRunning)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if((e.button.x <= 780) && (e.button.x >= 730) && (e.button.y <= 60) && (e.button.y >= 15))
            {
                Mix_PlayChannel(-1, selectedSound, 0);
                SDL_Texture* Sound = NULL;
                if(Mix_PlayingMusic())
                {
                    Sound = loadTexture("image/muteSound.png", renderer);
                    Mix_HaltMusic();
                }
                else
                {
                    Sound = loadTexture("image/enableSound.png", renderer);
                    Mix_PlayMusic(backgroundMusic, -1 );
                }
                SDL_RenderCopy(renderer, Sound, NULL, &soundRect);
                SDL_RenderPresent(renderer);
                SDL_Delay(50);
            }
            else if((e.button.x <= 510) && (e.button.x >= 320) && (e.button.y <= 460) && (e.button.y >= 380))
            {
                Mix_PlayChannel(-1, selectedSound, 0);
                SDL_Delay(100);
                isRunning = false;
            }
        }
    }
}

void Game::gameLevel()
{
    bool isRunning = true;
    SDL_Texture* select = loadTexture("image/selectLevel.png", renderer);
    SDL_RenderCopy(renderer, select, NULL, NULL);
    SDL_RenderPresent(renderer);

    targetPoint = 10000;
    while (isRunning)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if((e.button.x <= 490) && (e.button.x >= 310))
            {
                Mix_PlayChannel(-1, selectedSound, 0);
                if(e.button.y <= 400 && e.button.y >= 350)
                {
                    Level = 1;
                    Move = 25;
                    isRunning = false;
                }
                else if(e.button.y <= 475 && e.button.y >= 420)
                {
                    Level = 2;
                    Move = 20;
                    isRunning = false;
                }
                else if(e.button.y <= 560 && e.button.y >= 507)
                {
                    Level = 3;
                    Move = 10;
                    isRunning = false;
                }
            }
        }
    }
}

int Game::gamePlay()
{
    int yourMove = Move;
    int Point = 0;
    SDL_Texture* image = loadTexture("image/gameboard.png", renderer);
    SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
    gameBoard game_board(renderer);
    loadFont("00000", renderer, yourScore);
    loadFont("10000", renderer, TargetScore);
    string moveString = to_string(Move);
    const char* Movee = moveString.c_str();
    loadFont(Movee, renderer, MoveRect);
    game_board.fillBoard(Level);
    bool isRunning = false;
    while (!isRunning)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            while(!game_board.checkPossibleMove())
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &title);
                loadFont("No Possible move!", renderer, title);
                SDL_Delay(100);
                SDL_RenderFillRect(renderer, &title);
                loadFont("Mix Tiles!", renderer, title);
                game_board.mixTile();
                game_board.renderBoard();
            }
            game_board.selectTile(e.button.x, e.button.y, yourMove);
            while(game_board.findMatch(Point))
            {
                SDL_SetRenderDrawColor(renderer, 255, 170, 200, 0);
                SDL_RenderFillRect(renderer, &MoveRect);
                string tempMove = to_string(yourMove);
                const char* playerMove = tempMove.c_str();
                loadFont(playerMove, renderer, MoveRect);
                game_board.dropTile(Point, Level);
            }
            if(Point >= targetPoint)
                return gameResult(1);
            else if(yourMove == 0)
                return gameResult(0);
        }
    }
}

Game::gameResult(int res)
{
    if(res == 1)
    {
        Mix_PlayMusic(winMusic, -1);
        SDL_Texture* image = loadTexture("image/win.png", renderer);
        SDL_RenderCopy(renderer, image, NULL, NULL);
        SDL_RenderPresent(renderer);
        return 1;
    }
    else
    {
        Mix_PlayMusic(gameOverMusic, -1);
        SDL_Texture* image = loadTexture("image/GameOver.png", renderer);
        SDL_RenderCopy(renderer, image, NULL, NULL);
        SDL_RenderPresent(renderer);
        return 0;
    }
}

bool Game::gamePlayAgain()
{
    while (true)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(e.button.x <= 485 && e.button.x >= 310)
            {
                Mix_PlayChannel(-1, selectedSound, 0);
                if(e.button.y <= 400 && e.button.y >= 320)
                    return 1;
                else if(e.button.y <= 500 && e.button.y >= 395)
                    return 0;
            }
        }
    }
}

