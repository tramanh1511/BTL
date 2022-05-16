#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "SDL_mixer_basic.h"

using namespace std;

Mix_Music *backgroundMusic = NULL;
Mix_Chunk *selectedSound = NULL;
Mix_Chunk *eatableSound = NULL;

bool loadMusic()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cerr << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError();
		success = false;
	}
    //Init SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
        success = false;
    }
    selectedSound = Mix_LoadWAV("sound/selectedSound.mp3");
    if (selectedSound == NULL)
    {
        cerr << "Failed to load the sound effect! SDL_mixer Error: " << Mix_GetError() << "\n";
        success = false;
    }
    eatableSound = Mix_LoadWAV("sound/eatableSound.mp3");
    if (selectedSound == NULL)
    {
        cerr << "Failed to load the sound effect! SDL_mixer Error: " << Mix_GetError() << "\n";
        success = false;
    }
    //Load Music
    backgroundMusic = Mix_LoadMUS("sound/backgroundMusic.wav");
    if (backgroundMusic == NULL)
    {
         cerr << "Failed to load the background music! SDL_mixer Error: " << Mix_GetError() << "\n";
        success = false;
    }
    return success;
}

void closeMusic()
{
    //Free the sound effects
    Mix_FreeChunk(eatableSound);
    Mix_FreeChunk(selectedSound);
    eatableSound = NULL;
    selectedSound = NULL;
    //Free the music
    Mix_FreeMusic(backgroundMusic);
    backgroundMusic = NULL;
    Mix_Quit();
}
