#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/assetmanager.h"

/**
 * Load textures.
 */
bool loadAssets(SDL_Renderer* renderer, AssetRegistry* reg, char* filepath) {
    // How many textures are we loading?
    int total = 0;
    char buffer[100];
    // Open file and count how many lines
    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        printf("Unable to find specified asset manifest file.\n");
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
    reg->registry = (RegisteredAsset*) malloc(sizeof(RegisteredAsset) * reg->totalSize);
    reg->currentSize = 0;
    // Loop each line and load the texture.
    printf("Loading textures.....\n");
    while(fgets(buffer, sizeof(buffer), fp)) {
        // If last character of buffer is a newline, strip it
        int blen = strlen(buffer);
        if (buffer[blen - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (!loadAsset(renderer, buffer, &reg->registry[reg->currentSize])) {
            // Unable to load?
            fprintf(stderr, "Could not load file: %s\n", buffer);
            memset(buffer, '\0', sizeof(buffer));
            continue;
        }
        // Let the registry know we have added an asset.
        // Set the texture's unique id
        reg->registry[reg->currentSize].uniqueID = reg->currentSize;
        reg->currentSize++;
        memset(buffer, '\0', sizeof(buffer));
    }
    fclose(fp);
    return true;
}

/**
 *  Load a texture into the manager.
 */
bool loadAsset(SDL_Renderer* renderer, char* path, RegisteredAsset* asset) {
    // Set the texture's reference string and check the asset type.
    if (!typeAsset(asset, path)) {
        printf("Unable to type asset.\n");
        return false;
    }
    switch (asset->type) {
        case Texture:
            asset->pointer.texture = IMG_LoadTexture(renderer, path);
            break;
        case Font:
            asset->pointer.font = TTF_OpenFont(path, 20);
        case Sound:
            break;
        default:
            return false;
    }
    printf("Successfully loaded %s\n", asset->reference);
    return true;
}

/**
 * Determine the type of the asset and set the filename and type.
 */
bool typeAsset(RegisteredAsset* asset, char* path) {
    // Parse filename to get extention.
    char* filename = strtok(path, "/");
    while (strtok(NULL, "/") != NULL) {
        filename = strtok(NULL, "/");
    }
    asset->reference = (char*) malloc(sizeof(char) * strlen(filename) + 1);
    strcpy(asset->reference, filename);
    printf("%s %s\n", filename, asset->reference);
    char* ext = strtok(filename, ".");
    while (strtok(NULL, ".") != NULL) {
        ext = strtok(NULL, ".");
    }
    printf("%s\n", ext);
    // Determine which load function to use
    if (!strcmp(ext, ".png") || !strcmp(ext, ".jpg")) {
        asset->type = Texture;
    } else if (!strcmp(ext, ".ttf") || !strcmp(ext, ".otf")) {
        asset->type = Font;
    } else if (!strcmp(ext, ".ogg") || !strcmp(ext, ".mp3")) {
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
bool freeAsset(RegisteredAsset* asset) {
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
            printf("Asset type unknown, unable to free.\n");
            return false;
            break;
    }
    // Free asset reference name.
    if (asset->reference) {
        printf("Freed %s\n", asset->reference);
        free(asset->reference);
        asset->reference = NULL;
    } else {
        printf("Reference name not allocated to begin with...\n");
        return false;
    }
    return true;
}

/**
 * Free all assets in registry.
 */
bool freeAssets(AssetRegistry* reg) {
    int freed = 0;
    for (int i = 0; i < reg->currentSize; i++) {
        if (!freeAsset(&reg->registry[i])) {
            printf("Failed to free asset in position %d.\n", i);
        }
        freed++;
    }
    printf("Freed %d textures out of %d.\n", freed, reg->totalSize);
    return true;
}
