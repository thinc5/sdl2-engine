#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/texturemanager.h"

/**
 *  Load a texture into the manager.
 */
bool loadTexture(SDL_Renderer* renderer, char* filename, TextureRegistry* reg) {
    // Load texture from path.
    SDL_Surface* sur;
    sur = loadSurface(filename);
    if (sur == NULL) {
        printf("Failed to create surface, check path.\n");
        return false;
    }
    // Optimise surface?
    //SDL_Surface* surOp;

    // Create new entry into the registry.
    // Point to the next uninitilized texture space
    RegisteredTexture* newRT = &reg->registry[reg->currentSize];
    newRT->texture = SDL_CreateTextureFromSurface(renderer, sur);
    SDL_FreeSurface(sur);
    if (newRT->texture == NULL) {
        printf("Failed to create texture from surface..\n");
        return false;
    }
    // Set the texture's unique id
    newRT->uniqueID = reg->currentSize;
    // Set the texture's reference string.
    newRT->reference = (char*) malloc(sizeof(char) * strlen(filename));
    if (strcpy(newRT->reference, filename) == NULL) {
        // Failed to copy string, free texture and return false.
        SDL_DestroyTexture(newRT->texture);
        printf("Failed to copy filename into registry\n");
        return false;
    }
    // Let the registry know we have added a texture.
    reg->currentSize++;
    printf("Successfully loaded %s\n", newRT->reference);
    return true;
}

/**
 * Free an entry in the texture registry.
 */
bool freeTexture(RegisteredTexture* tex) {
    free(tex->reference);
    tex->reference = NULL;
    SDL_DestroyTexture(tex->texture);
    tex->texture = NULL;
    return true;
}

/**
 * Free all textures in registry.
 */
bool freeTextures(TextureRegistry* reg) {
    for (int i = reg->totalSize; i > 0; i--) {
        if (!freeTexture(&reg->registry[i - 1])) {
            printf("Failed to free texure in position %d.\n", i);
        }
        reg->currentSize--;
    }
    printf("Freed %d textures out of %d.\n", reg->currentSize, reg->totalSize);
    return true;
}

/**
 * Loading surface from provided path
 */
SDL_Surface* loadSurface(char* path) {
    printf("loading %s..\n", path);
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

