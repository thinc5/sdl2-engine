#ifndef ASSET_H
#define ASSET_H

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
    Sound,
    AssetTypes
};

static const char* const AssetTypeValue[AssetTypes] = {
    "Texture",
    "Font",
    "Sound"
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
 *  Load an asset into the manager.
 */
bool load_asset(SDL_Renderer* renderer, const char* path, RegisteredAsset* reg);

/**
 * Determine the type of the asset and set the filename and type.
 */
bool type_asset(RegisteredAsset* asset, const char* path);

/**
 * Free an entry in the texture registry.
 */
bool free_asset(RegisteredAsset* asset);

#endif
