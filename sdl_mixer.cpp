#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

Mix_Music *music = NULL;
Mix_Chunk *chunk = NULL;

bool loadMedia()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError();
		success = false;
	}
    //Init SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
        success = false;
    }
    //Load Sound Effect
    chunk = Mix_LoadWAV("beat.wav");
    if (chunk == NULL)
    {
        cout << "Failed to load the sound effect! SDL_mixer Error: " << Mix_GetError() << "\n";
        success = false;
    }

    //Load Music
    music = Mix_LoadMUS("Nhat-Nhoa-Mua-Phai-Huong-Ly-Son-Vie.mp3");
    if (music == NULL)
    {
         cout << "Failed to load the background music! SDL_mixer Error: " << Mix_GetError() << "\n";
        success = false;
    }
    return success;

}

void closeMedia()
{
    //Free the sound effects
    Mix_FreeChunk(chunk);
    chunk = NULL;
    //Free the music
    Mix_FreeMusic(music);
    music = NULL;
    Mix_Quit();
}
