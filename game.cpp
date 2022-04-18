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
//    if (!LoadMusic()) cerr << "Failed to load music!" << endl;
//    Mix_VolumeChunk(eatable_sound, 32);
//    Mix_VolumeChunk(selected_sound, 64);
//    Mix_VolumeChunk(reverse_sound, 32);
//    Mix_VolumeMusic(16);
// Show_image(renderer, background_img, back_rect);
//    Show_image(renderer, playbutton, play_rect);
//    Mix_PlayMusic(background_music, -1);
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
                //  if(!Mix_Paused(-1)) Mix_PlayChannel(-1, reverse_sound, 0);
                // Show_image(renderer, playbuttondown, play_rect);
                SDL_Texture* image = loadTexture("image/gameboard.png", renderer);
                SDL_RenderCopy(renderer, image, NULL, NULL);
                SDL_RenderPresent(renderer);
                SDL_Delay(10);
                quit = false;
            }
        }
    }
}

int Game::result(bool res)
{
    // if (res) loadFont("You Win!!!", renderer, Title_rect);
    //else loadFont("You Lose!!!", renderer, Title_rect);
    SDL_RenderPresent(renderer);
}

int Game::gamePlay()
{
    gameBoard game_board = renderer;
    game_board.fillBoard();
    int Point(0), moveHiden = Move;
//    LoadFont("000000", renderer, urScore);
//    LoadFont(IntTostr(target_point), renderer, TarScore);
//    LoadFont("Moves:", renderer, MoveRect);
//    SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
//    SDL_RenderFillRect(renderer, &MoveNum);
//    LoadFont(moveStr(moveHid), renderer, MoveNum);
//    game_board.Fill_board();
    bool quit = false;
    while (!quit)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            while(game_board.checkPossibleMove())
            {
//                SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
//                SDL_RenderFillRect(renderer, &urScore);
//                LoadFont("No Possible move!", renderer, urScore);
                SDL_Delay(100);
//                SDL_RenderFillRect(renderer, &urScore);
//                LoadFont("Mix Tiles!", renderer, urScore);
                game_board.mixTile();
                game_board.renderBoard();
            }
            game_board.findTileSelected(e.button.x, e.button.y, moveHiden);
            while(game_board.findMatch(Point))
            {
//               SDL_RenderFillRect(renderer, &MoveNum);
//                LoadFont(moveStr(moveHid), renderer, MoveNum);
                game_board.dropTile(Point);
//                 SDL_RenderFillRect(renderer, &urScore);
//                LoadFont(IntTostr(point), renderer, urScore);
            }
            if(point >= targetPoint) return result(true);
            else if(moveHiden == 0) return result(false);
        }
    }
}
