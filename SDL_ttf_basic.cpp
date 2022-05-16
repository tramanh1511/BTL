#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include "SDL_ttf_basic.h"

using namespace std;

TTF_Font* Font = NULL;
SDL_Surface* Surface = NULL;
SDL_Texture* Texture = NULL;

void loadFont(const char* Text, SDL_Renderer* renderer, SDL_Rect textRect)
{
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
        cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
    else
    {
        Font = TTF_OpenFont("font/AGENCYB.TTF", 30);
        if(Font == NULL)
            cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << "\n";
        else
        {
            //Render text
            SDL_Color textColor = { 240, 0, 240, 255 };
            Surface = TTF_RenderText_Solid(Font, Text, textColor);
            Texture = SDL_CreateTextureFromSurface(renderer, Surface);
            SDL_RenderCopy(renderer, Texture, NULL, &textRect);
            SDL_RenderPresent(renderer);
            SDL_FreeSurface(Surface);
        }
    }
    TTF_CloseFont(Font);
    Font = NULL;
    SDL_DestroyTexture(Texture);
    Texture = NULL;
    TTF_Quit();
}
