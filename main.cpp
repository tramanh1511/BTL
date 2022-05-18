#include <bits/stdc++.h>
#include <SDL.h>
#include "SDL_utils.h"
#include "SDL_mixer_basic.h"
#include "SDL_ttf_basic.h"
#include "SDL_image_basic.h"
#include "Game.h"


using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string& WINDOW_TITLE = "Candy Crush Suga";


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    srand(int(time(NULL)));
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    // Your drawing code here
    SDL_Event e;
    bool isRunning = false;
    while(!isRunning)
    {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        Game game(renderer, e);
        game.initializeGame();
        while(!isRunning)
        {
            int res = game.gamePlay();
            if(res == 0 || res == 1)
            {
                //isRunning = true;
                SDL_Delay(100);
                continue;
            }
        }
        //  if(isRunning == true) isRunning = false;
    }
    closeMusic();
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
