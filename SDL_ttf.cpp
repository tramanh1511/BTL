#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

TTF_Font* Font = NULL;
SDL_Surface* Surface = NULL;
SDL_Texture* Texture = NULL;

bool loadFont(const char* Text, SDL_Renderer* renderer, SDL_Rect Text_rect)
{
    bool success = true;
    Font = TTF_OpenFont("VeraMoBd.ttf", 30);
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
        success = false;
    }
    if(Font == NULL)
    {
        cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << "\n";
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 255, 255, 255 };
        Surface = TTF_RenderText_Solid(Font, Text, textColor);
        Texture = SDL_CreateTextureFromSurface(renderer, Surface);
        SDL_RenderCopy(renderer, Texture, NULL, &Text_rect);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(Surface);
    }
    TTF_CloseFont(Font);
	Font = NULL;
	SDL_DestroyTexture(Texture);
	Texture = NULL;
	TTF_Quit();
}
