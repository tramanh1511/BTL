#include <bits/stdc++.h>
#include <SDL_mixer.h>
#include "SDL_mixer_basic.h"
#include "SDL_utils.h"
#include "gameBoard.h"

using namespace std;

void gameBoard::renderBoard()
{
    for(int i = 0; i < boardRow; i++)
        for(int j = 0; j < boardCol; j++)
            tileBoard[i][j].render();
}

void gameBoard::fillBoard()
{
    for(int i = 0; i < boardCol; i++)
    {
        for(int j = 0; j < boardRow; j++)
        {
            tileBoard[i][j].type = rand() % numOfTile + 1;
            tileBoard[i][j].tileRect.x = i*63;
            tileBoard[i][j].tileRect.y = j*63;
        }
    }
    for(int i = 0; i < boardCol; i++)
        for(int j = 0; j < boardRow; j++)
        {
            tileBoard[i][j].renderer = renderer;
            tileBoard[i][j].render();
        }
}

bool gameBoard::findMatch(int& countPoint)
{
    speed = 25;
    for(int i = 0; i< boardRow; i++)
    {
        int temp(1), j(0);
        while(j < boardCol - 2)
        {
            while(temp < boardCol && tileBoard[i][j].type == tileBoard[i][temp].type) temp++;
            if(temp - j >= 3)
            {
                if(temp - j > 3) speed = 60;
                countPoint += (temp - j) * 100;
                for(int k = j; k < temp; k++)
                {
//                    if(!Mix_Paused(-1))
//                    {
//                        Mix_Pause(1);
//                        Mix_PlayChannel(1, Sound1, 0);
//                    }
                    tileBoard[i][k].tile_status = tileStatus::Empty;
                    tileBoard[i][k].renderEmpty();
                }
                SDL_RenderPresent(renderer);
            }
            j = temp;
        }
    }

    for(int j = 0; j<boardCol; j++)
    {
        int temp(1), i(0);
        while(temp < boardRow && tileBoard[i][j].type == tileBoard[temp][j].type) temp++;
        {
            if(temp - i >=3)
            {
                if(temp - i > 3) speed = 60;
                countPoint += (temp - i)*100;
                for(int k=i; k<temp; k++)
                {
//                    if (!Mix_Paused(-1))
//                    {
//                        Mix_Pause(1);
//                        Mix_PlayChannel(1, Sound1, 0);
//                    }
                    tileBoard[temp][j].type = tileStatus::Empty;
                    tileBoard[temp][j].renderEmpty();
                }
                SDL_RenderPresent(renderer);
            }
            i = temp;
        }
    }
    for(int i=0; i<boardRow; i++)
        for(int j=0; j<boardCol; j++)
            if(tileBoard[i][j].type == tileStatus::Empty) return true;
    return false;
}

bool gameBoard::findTileSelected(int xmouse, int ymouse, int& Move)
{
    // if (!Mix_Paused(-1)) Mix_PlayChannel(-1, SelectedSound, 0);
    static int countSelect = 0;
    static int tempR = 0, tempC = 0;
    for(int i=0; i<boardRow; i++)
    {
        for(int j=0; j<boardCol; j++)
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
                        for(int u = tempR-1; u <= tempR+1; u++)
                            for(int v = tempC - 1; v <= tempC+1; v++)
                                if(i == u && j == v)
                                {
                                    swap(tileBoard[i][j].type, tileBoard[tempR][tempC].type);
                                    tileBoard[i][j].swapTile(tileBoard[tempR][tempC]);
                                    tileBoard[i][j].render();
                                    tileBoard[tempR][tempC].render();
                                    if(!findMatch(hiddenPoint))
                                    {
                                        swap(tileBoard[i][j].type, tileBoard[tempR][tempC].type);
                                        // if (!Mix_Paused(-1)) Mix_PlayChannel(1, reverse_sound, 0);
                                        tileBoard[tempR][tempC].swapTile(tileBoard[i][j]);
                                    }
                                }
                        tileBoard[i][j].render();
                        tileBoard[tempR][tempC].render();
                        countSelect = 0;
                    }
                    break;
                }
                else if (tileBoard[i][j].tile_status == tileStatus::Selected)
                {
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
            if(tempBoard.findMatch(hiddenPoint)) return true;
            swap(tempBoard.tileBoard[i][j].type, tempBoard.tileBoard[i][j+1].type);
        }
    for(int i = 0; i < boardCol; i++)
        for(int j = 0; j < boardRow - 1; j++)
        {
            swap(tempBoard.tileBoard[i][j].type, tempBoard.tileBoard[i+1][j].type);
            if(tempBoard.findMatch(hiddenPoint)) return true;
            swap(tempBoard.tileBoard[i][j].type, tempBoard.tileBoard[i+1][j].type);
        }
    return false;
}

void gameBoard::dropTile(int& Point)
{
    for(int j = 0; j < boardCol; j++)
    {
        static int k = 0;
        for(int i = boardRow - 1; i >= 0; i--)
            if(tileBoard[i][j].tile_status == tileStatus::Empty)
            {
                for(int k = i-1; k>=0; k--)
                {
                    if(tileBoard[k][j].tile_status != tileStatus::Empty)
                    {
                        tileBoard[i][j].type = tileBoard[k][j].type;
                        tileBoard[k][j].tile_status = tileStatus::Empty;
                        if(speed != 60)
                        {
                            if(i - k >= 3) speed = 50;
                            else speed = 25;
                        }
                        for(int temp = k; temp < i;)
                            tileBoard[temp][i].swapTile(tileBoard[temp++][j], tileBoard[k][j].texture, speed);
                        tileBoard[i][j].render();
                        break;
                    }
                    else continue;
                }
            }
        for(int i = boardRow - 1; i >= 0; i--)
        {
            if (tileBoard[i][j].tile_status == tileStatus::Empty)
            {
                for(k = i; k>=0; k--)
                {
                    tileBoard[0][i].type = rand() % numOfTile + 1;
                    tileBoard[0][i].render();
                    if(k == 0) break;
                    tileBoard[k][j].type = tileBoard[0][j].type;
                    tileBoard[0][j].tile_status = tileStatus::Empty;
                    tileBoard[0][i].renderEmpty();
                    if(speed != 65)
                    {
                        if(i - k >= 3) speed = 50;
                        else speed = 25;
                    }
                    for(int temp = 0; temp < k;)
                        tileBoard[temp][j].swapTile(tileBoard[temp++][j], tileBoard[0][j].texture, speed);
                    tileBoard[k][j].render();
                }
            }
        }
    }
}

void gameBoard::mixTile()
{
    int tempBoard[boardRow][boardCol];
    bool checkFill[boardRow][boardCol] = {0};
    for(int i = 0; i<boardRow; i++)
        for(int j=0; j<boardCol; j++)
        tempBoard[i][j] = tileBoard[i][j].type;
    for(int i=0; i<boardRow; i++)
        for(int j=0; j<boardCol; j++)
    {
        int m = rand() % boardRow;
        int n = rand() % boardCol;
        while(checkFill[m][n]) j--;
        tileBoard[m][n].type = tempBoard[i][j];
        checkFill[m][n] = 0;
    }
    if(!checkPossibleMove()) mixTile();
}



