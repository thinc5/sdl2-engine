#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

/**
 * Enumeration of each asset type.
 * How we know what type each registry asset is.
 */
enum AssetType {
    Texture,
    Font,
    Sound
};

/**
 * Each possible asset type.
 */
typedef union AssetPointer {
    SDL_Texture* texture;
    TTF_Font* font;
    Mix_Chunk* sound;
} AssetPointer;

/**
 * Each texture to be registered.
 */
typedef struct RegisteredAsset {
    int uniqueID;
    enum AssetType type;
    char* reference;
    AssetPointer pointer;
} RegisteredAsset;

/**
 * The Registry of all loaded textures.
 */
typedef struct AssetRegistry {
    unsigned int currentSize;
    unsigned int totalSize;
    RegisteredAsset* registry;
} AssetRegistry;

/**
 * Load assets from a newline-delimated plain text file.
 */
bool loadAssets(SDL_Renderer* renderer, AssetRegistry* reg, char* configPath);

/**
 *  Load a texture into the manager.
 */
bool loadAsset(SDL_Renderer* renderer, char* path, RegisteredAsset* reg);

/**
 * Determine the type of the asset and set the filename and type.
 */
bool typeAsset(RegisteredAsset* asset, char* path);

/**
 * Free all assets from a provided registry.
 */
bool freeAssets(AssetRegistry* reg);

#endif