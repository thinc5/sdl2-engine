#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

#include "./asset.h"

/**
 * The Registry of all loaded textures.
 */
typedef struct AssetRegistry {
    unsigned int currentSize;
    unsigned int totalSize;
    RegisteredAsset* registry;
} AssetRegistry;

/**
 * Initialize the asset manager.
 */
bool initAssetManager(AssetRegistry* reg);

/**
 * Load assets from a newline-delimated plain text file.
 */
bool loadAssets(SDL_Renderer* renderer, AssetRegistry* reg, const char* configPath);

/**
 *  Load an asset into the manager.
 */
bool loadAsset(SDL_Renderer* renderer, const char* path, RegisteredAsset* reg);

/**
 * Determine the type of the asset and set the filename and type.
 */
bool typeAsset(RegisteredAsset* asset, const char* path);

/**
 * Free all assets from a provided registry.
 */
bool freeAssets(AssetRegistry* reg);

/**
 * If an asset is found with provided reference, return pointer to asset, else return NULL.
 */
RegisteredAsset* getAssetByReference(const char* reference, AssetRegistry* reg);

#endif
