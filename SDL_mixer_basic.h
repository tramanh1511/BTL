#ifndef SDL_mixer_basic.h
#define SDL_mixer_basic.h
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

extern Mix_Music *backgroundMusic;
extern Mix_Music *winMusic;
extern Mix_Music *gameOverMusic;
extern Mix_Chunk *selectedSound;
extern Mix_Chunk *eatableSound;
extern Mix_Chunk *reverseSound;

bool loadMusic();
void closeMusic();
#endif // SDL_mixer_basic
