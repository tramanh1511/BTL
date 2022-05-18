#include <bits/stdc++.h>
#include <SDL_mixer.h>
#include "SDL_mixer_basic.h"
#include "SDL_ttf_basic.h"
#include "SDL_utils.h"
#include "gameBoard.h"

using namespace std;

SDL_Rect YourScore = {45, 310, 120, 50};

void gameBoard::renderBoard()
{
    for(int i = 0; i < boardRow; i++)
        for(int j = 0; j < boardCol; j++)
        {
            tileBoard[i][j].renderer = renderer;
            tileBoard[i][j].render();
        }

}

void gameBoard::fillBoard()
{
    for(int i = 0; i < boardRow; i++)
    {
        for (int j = 0; j < boardCol;)
        {
            j = max(0,j);
            tileBoard[i][j].type = 1 + rand() % (numOfTile-1);
            tileBoard[i][j].tileRect.x = 220 + i*63;
            tileBoard[i][j].tileRect.y =  20 + j*63;
            if (j >= 2 && (tileBoard[i][j].type == tileBoard[i][j-1].type)
                    && (tileBoard[i][j-1].type == tileBoard[i][j-2].type))
            {
                j--;
                continue;
            }
            if (i >= 2 && (tileBoard[i][j].type == tileBoard[i-1][j].type)
                    && (tileBoard[i-1][j].type == tileBoard[i-2][j].type))
            {
                j--;
                continue;
            }
            j++;
        }
    }
    for(int i = 0; i < boardRow; i++)
        for(int j = 0; j < boardCol; j++)
        {
            tileBoard[i][j].renderer = renderer;
            tileBoard[i][j].renderEmpty();
            tileBoard[i][j].render();
        }
}

bool gameBoard::findMatch(int& countPoint)
{
    for (int i = 0; i < boardRow; i++)
    {
        int k = 1;
        for (int j = 0; j < boardCol - 2;)
        {
            if ( k < boardCol && tileBoard[i][j].type == tileBoard[i][k].type)
            {
                k++;
                continue;
            }
            if (k - j >= 3)
            {
                SDL_Delay(100);
                countPoint += (k - j) * 100;
                string point = to_string(countPoint);
                const char* pointt = point.c_str();
                SDL_SetRenderDrawColor(renderer, 255, 170, 200, 0);
                SDL_RenderFillRect(renderer, &YourScore);
                loadFont(pointt, renderer, YourScore);
                for (int temp = j; temp < k; temp++)
                {
                    SDL_Delay(10);
                    tileBoard[i][temp].tile_status = tileStatus::Empty;
                    if (!Mix_Paused(-1))
                    {
                        Mix_Pause(1);
                        Mix_PlayChannel(1, eatableSound, 0);
                    }
                    tileBoard[i][temp].renderEmpty();
                }
                SDL_RenderPresent(renderer);
            }
            j = k;
        }
    }
    for (int j = 0; j < boardCol; j++)
    {
        int k = 1;
        for (int i = 0; i < boardRow - 2;)
        {
            if ( k < boardRow && tileBoard[i][j].type == tileBoard[k][j].type)
            {
                k++;
                continue;
            }
            if (k - i >= 3)
            {
                SDL_Delay(100);
                countPoint += (k - i) * 100;
                string point = to_string(countPoint);
                const char* pointt = point.c_str();
                SDL_SetRenderDrawColor(renderer, 255, 170, 200, 0);
                SDL_RenderFillRect(renderer, &YourScore);
                loadFont(pointt, renderer, YourScore);
                for (int temp = i; temp < k; temp++)
                {
                    SDL_Delay(10);
                    tileBoard[temp][j].tile_status = tileStatus::Empty;
                    if (!Mix_Paused(-1))
                    {
                        Mix_Pause(1);
                        Mix_PlayChannel(1, eatableSound, 0);
                    }
                    tileBoard[temp][j].renderEmpty();
                }
                SDL_RenderPresent(renderer);
            }
            i = k;
        }
    }
    for (int i = 0; i < boardRow; i++)
        for (int j = 0; j < boardCol; j++)
            if (tileBoard[i][j].tile_status == tileStatus::Empty)
                return true;
    return false;

}

bool gameBoard::selectTile(int xmouse, int ymouse, int& Move)
{
    if (!Mix_Paused(-1)) Mix_PlayChannel(-1, selectedSound, 0);
    static int countSelect = 0;
    static int tempR = 0, tempC = 0;
    for(int i = 0; i < boardRow; i++)
    {
        for(int j = 0; j < boardCol; j++)
        {
            if((xmouse < tileBoard[i][j].tileRect.x + tileBoard[i][j].tileRect.w) && (xmouse >= tileBoard[i][j].tileRect.x)
                    && (ymouse < tileBoard[i][j].tileRect.y + tileBoard[i][j].tileRect.h) && (ymouse >= tileBoard[i][j].tileRect.y))
            {
                if(tileBoard[i][j].tile_status != tileStatus::Selected && tileBoard[i][j].tile_status != tileStatus::Empty && countSelect <=1)
                {
                    countSelect++;
                    if(countSelect == 1)
                    {
                        tempR = i;
                        tempC = j;
                    }
                    tileBoard[i][j].tile_status = tileStatus::Selected;
                    tileBoard[i][j].renderSelected();
                    if(countSelect == 2)
                    {
                        Move --;
                        if (((i == tempR - 1 && j == tempC) || (i == tempR + 1 && j == tempC) ||
                                (i == tempR && j == tempC - 1) || ((i == tempR && j == tempC + 1))))
                        {
                            swap(tileBoard[i][j].type, tileBoard[tempR][tempC].type);
                            tileBoard[i][j].swapTile(tileBoard[tempR][tempC]);
                            tileBoard[i][j].render();
                            tileBoard[tempR][tempC].render();
                            if(!findMatch(hiddenPoint))
                            {
                                swap(tileBoard[i][j].type, tileBoard[tempR][tempC].type);
                                if (!Mix_Paused(-1)) Mix_PlayChannel(1, reverseSound, 0);
                                tileBoard[tempR][tempC].swapTile(tileBoard[i][j]);
                            }
                            tileBoard[i][j].render();
                            tileBoard[tempR][tempC].render();
                        }
                        else
                        {
                            tileBoard[i][j].renderEmpty();
                            tileBoard[i][j].render();
                            tileBoard[tempR][tempC].renderEmpty();
                            tileBoard[tempR][tempC].render();
                        }
                        countSelect = 0;
                    }
                    break;
                }
                else if (tileBoard[i][j].tile_status == tileStatus::Selected)
                {
                    tileBoard[i][j].renderEmpty();
                    tileBoard[i][j].render();
                    countSelect--;
                }
            }
        }
    }
}

bool gameBoard::checkPossibleMove()
{
    gameBoard tempBoard;
    for(int i = 0; i < boardRow; i++)
        for(int j = 0; j < boardCol; j++)
            tempBoard.tileBoard[i][j].type = tileBoard[i][j].type;
    for(int i = 0; i < boardRow; i++)
        for(int j = 0; j < boardCol - 1; j++)
        {
            swap(tempBoard.tileBoard[i][j].type, tempBoard.tileBoard[i][j+1].type);
            if(tempBoard.findMatch(hiddenPoint))
                return true;
            swap(tempBoard.tileBoard[i][j].type, tempBoard.tileBoard[i][j+1].type);
        }
    for(int i = 0; i < boardCol - 1; i++)
        for(int j = 0; j < boardRow; j++)
        {
            swap(tempBoard.tileBoard[i][j].type, tempBoard.tileBoard[i+1][j].type);
            if(tempBoard.findMatch(hiddenPoint)) return true;
            swap(tempBoard.tileBoard[i][j].type, tempBoard.tileBoard[i+1][j].type);
        }
    return false;
}

void gameBoard::dropTile(int& Point)
{
    for(int i = 0; i < boardRow; i++)
        for(int j = 0; j < boardCol; j++)
        {
            if(tileBoard[i][j].tile_status == tileStatus::Empty)
            {
                SDL_Delay(100);
                tileBoard[i][j].type = 1 + rand() % (numOfTile-1);
                tileBoard[i][j].render();
            }
        }
}

void gameBoard::mixTile()
{
    int tempBoard[boardRow][boardCol];
    bool checkFill[boardRow][boardCol] = {0};
    for(int i = 0; i < boardRow; i++)
        for(int j = 0; j < boardCol; j++)
            tempBoard[i][j] = tileBoard[i][j].type;
    for(int i = 0; i < boardRow; i++)
        for(int j = 0; j < boardCol; j++)
        {
            int m = rand() % boardRow;
            int n = rand() % boardCol;
            while(checkFill[m][n]) j--;
            tileBoard[m][n].type = tempBoard[i][j];
            checkFill[m][n] = 0;
        }
    while(!checkPossibleMove()) mixTile();
}



