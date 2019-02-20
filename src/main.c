#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../include/config.h"

SDL_Surface* loadSurface( char* path );

/**
 * Entry point for Engine.
 */
int WinMain(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    // Init sdl
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create the window
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Load haha
    SDL_Surface* alexS;
    alexS = loadSurface("res/alex.jpg");
    SDL_Texture* alexT = SDL_CreateTextureFromSurface(renderer, alexS);
    SDL_FreeSurface(alexS);


    // Main game loop
    bool game = true;
    while (game) {
        
        while (SDL_PollEvent(&event)) {
            // If person wants to exit i.e. alt+f4 or clicking x
            if (event.type == SDL_QUIT) {
                // Clean up memory here and break main game loop
                printf("Caught SDL_QUIT, exiting now...\n");
                SDL_DestroyTexture(alexT);
                game = false;
            }

            // Draw
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, alexT, NULL, NULL);
            SDL_RenderPresent(renderer);

        }
    }

    SDL_Quit();
    return 0;
}

SDL_Surface* loadSurface( char* path )
{
    printf("loading %s\n..", path);
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, loadedSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}
