#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/managers/asset.h"
#include "../../include/managers/assetstack.h"

/**
 *  Load an asset into the manager.
 */
bool load_asset(SDL_Renderer* renderer, const char* path, RegisteredAsset* asset) {
    // Set the texture's reference string and check the asset type.
    if (!type_asset(asset, path)) {
        ERROR_LOG("Unable to type asset %s.\n", path);
        return false;
    }
    switch (asset->type) {
        case Texture:
            asset->pointer.texture = IMG_LoadTexture(renderer, path);
            if (asset->pointer.texture == NULL) {
                return false;
            }
            break;
        case Font:
            asset->pointer.font = TTF_OpenFont(path, 20);
            if (asset->pointer.font == NULL) {
                return false;
            }
            break;
        case Sound:
            asset->pointer.sound = Mix_LoadWAV(path);
            if (asset->pointer.font == NULL) {
                return false;
            }
            break;
        default:
            return false;
    }
    return true;
}

/**
 * Determine the type of the asset and set the filename and type.
 */
bool type_asset(RegisteredAsset* asset, const char* path) {
    // Parse filename to get extention.
    char copy[strlen(path)];
    strcpy(copy, path);
    char* filename = strtok(copy, "/");
    while (1) {
        char* test = strtok(NULL, "/");
        if (test == NULL) {
            break;
        }
        filename = test;
    }
    asset->reference = (char*) malloc(sizeof(char) * strlen(filename) + 1);
    strcpy(asset->reference, filename);
    char* ext = strtok(filename, ".");
    while (1) {
        char* test = strtok(NULL, ".");
        if (test == NULL) {
            break;
        }
        ext = test;
    }
    // Determine which load function to use
    if (!strcmp(ext, "png") || !strcmp(ext, "jpg")) {
        asset->type = Texture;
    } else if (!strcmp(ext, "ttf") || !strcmp(ext, "otf")) {
        asset->type = Font;
    } else if (!strcmp(ext, "ogg") || !strcmp(ext, "mp3")) {
        asset->type = Sound;
    } else {
        // File type not supported.
        return false;
    }
    return true;
}

/**
 * Free an entry in the texture registry.
 */
bool free_asset(RegisteredAsset* asset) {
    // Free asset data.
    switch (asset->type) {
        case Texture:
            SDL_DestroyTexture(asset->pointer.texture);
            break;
        case Font:
            TTF_CloseFont(asset->pointer.font);
            break;
        case Sound:
            Mix_FreeChunk(asset->pointer.sound);
            break;
        default:
            ERROR_LOG("Asset type unknown, unable to free.\n");
            return false;
    }
    // Free asset reference name.
    if (asset->reference) {
        free(asset->reference);
        asset->reference = NULL;
    } else {
        ERROR_LOG("Reference name not allocated.\n");
        return false;
    }
    return true;
}

