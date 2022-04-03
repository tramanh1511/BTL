#include <bits/stdc++.h>
#include "SDL_utils.h"
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string& WINDOW_TITLE = "My Game";


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    // Your drawing code here


    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
