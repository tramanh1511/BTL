#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        cout<< "Unable to load Image "<< path <<" SDL_image Error: "
            << IMG_GetError()<<"\n";
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL)
            cout<< "Unable to create texture from "<< path <<" SDL Error: "
                << SDL_GetError() << "\n";
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
