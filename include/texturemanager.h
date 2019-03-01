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
typedef struct TextureRegistry {
    unsigned int currentSize;
    unsigned int totalSize;
    RegisteredTexture* registry;
} TextureRegistry;

/**
 * Load textures from a newline-delimated plain text file.
 */
bool loadTextures(SDL_Renderer* renderer, TextureRegistry* reg, char* configPath);

/**
 *  Load a texture into the manager.
 */
bool loadTexture(SDL_Renderer* renderer, char* filename, TextureRegistry* reg);

/**
 * Free all textures from a provided registry.
 */
bool freeTextures(TextureRegistry* reg);

/**
 * Load a surface from a provided filepath.
 */
SDL_Surface* loadSurface(char* path);

#endif