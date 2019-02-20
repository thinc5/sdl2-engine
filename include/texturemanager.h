#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>

#include <stdbool.h>

/**
 * Each texture to be registered.
 */
typedef struct RegisteredTexture {
    int uniqueID;
    char* reference;
    SDL_Texture* texture;
} RegisteredTexture;

/**
 * The Registry of all loaded textures.
 */
typedef struct TextureRegistry{
    unsigned int currentSize;
    unsigned int totalSize;
    RegisteredTexture* registry;
} TextureRegistry;

/**
 *  Load a texture into the manager.
 */
bool loadTexture(SDL_Renderer* renderer, char* filename, TextureRegistry* reg);


/**
 * 
 */
bool freeTextures(TextureRegistry* reg);

SDL_Surface* loadSurface(char* path);

#endif