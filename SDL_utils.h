#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <bits/stdc++.h>
#include <SDL.h>

using namespace std;

void logSDLError(ostream& os,
                 const string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
              const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const string& WINDOW_TITLE);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

#endif // SDL_utils

