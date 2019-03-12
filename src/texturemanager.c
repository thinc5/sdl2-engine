#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/texturemanager.h"

/**
 * Load textures.
 */
bool loadTextures(SDL_Renderer* renderer, TextureRegistry* reg, char* configPath) {
    // How many textures are we loading?
    int total = 0;
    char buffer[100];
    // Open file and count how many lines
    FILE* fp = fopen(configPath, "r");
    if (!fp) {
        printf("Unable to find specified texture configuration file.\n");
        return false;
    }
    while(fgets(buffer, sizeof(buffer), fp)) {
        total++;
    }
    // Reset the pointer back to the beginning of the file
    fseek(fp, 0, SEEK_SET);
    memset(buffer, '\0', sizeof(buffer));
    // Allocate space for each of the textures.
    reg->totalSize = total;
    reg->registry = (RegisteredTexture*) malloc(sizeof(RegisteredTexture) * reg->totalSize);
    reg->currentSize = 0;
    // Loop each line and load the texture.
    while(fgets(buffer, sizeof(buffer), fp)) {
        // If last character of buffer is a newline, strip it
        int blen = strlen(buffer);
        if (buffer[blen - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        // Remove newline
        if (!loadTexture(renderer, buffer, reg)) {
            fprintf(stderr, "Could not load file: %s\n", buffer);
            memset(buffer, '\0', sizeof(buffer));
            return false;
        }
        memset(buffer, '\0', sizeof(buffer));
    }
    fclose(fp);
    return true;
}

/**
 *  Load a texture into the manager.
 */
bool loadTexture(SDL_Renderer* renderer, char* filename, TextureRegistry* reg) {
    // Load texture from path.
    // SDL_Surface* sur = loadSurface(filename);
    // if (sur == NULL) {
    //     printf("Failed to create surface, check path.\n");
    //     printf("%d\n", (int)sur);
    //     return false;
    // }
    // Create new entry into the registry.
    // Point to the next uninitialized texture space
    RegisteredTexture* newRT = &reg->registry[reg->currentSize];
    newRT->texture = IMG_LoadTexture(renderer, filename);
    // SDL_FreeSurface(sur);
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
    if (tex->texture) {
        SDL_DestroyTexture(tex->texture);
        tex->texture = NULL;
    } else {
        printf("Texture was not allocated and cannot be freed\n");
    }
    if (tex->reference) {
        printf("Freed %s\n", tex->reference);
        free(tex->reference);
        tex->reference = NULL;
    } else {
        printf("Reference name not allocated to begin with...\n");
    }
    return true;
}

/**
 * Free all textures in registry.
 */
bool freeTextures(TextureRegistry* reg) {
    int freed = 0;
    for (int i = 0; i < reg->currentSize; i++) {
        if (!freeTexture(&reg->registry[i])) {
            printf("Failed to free texture in position %d.\n", i);
        }
        freed++;
    }
    printf("Freed %d textures out of %d.\n", freed, reg->totalSize);
    return true;
}

/**
 * Loading surface from provided path
 */
SDL_Surface* loadSurface(char* path) {
    // Load image at specified path
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return NULL;
    }
    // The final optimized image
    SDL_Surface* optimizedSurface = NULL;
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, loadedSurface->format, 0);
    if(optimizedSurface == NULL) {
        printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
    return optimizedSurface;
}

