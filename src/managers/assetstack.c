#include <stdlib.h>
#include <string.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/managers/assetstack.h"
#include "../../include/managers/asset.h"

/**
 * Initialize the asset stack.
 */
bool init_asset_stack(AssetStack* stack) {
    stack->allocations = -1;
    stack->heads = NULL;
    stack->tail = NULL;
    return true;
}

/**
 * Push and asset onto the stack.
 */
static bool push_asset(SDL_Renderer* renderer, AssetStack* stack, const char* asset_path) {
    if (stack->heads == NULL) {
        stack->heads = (AssetNode**) malloc(sizeof(AssetNode*));
    }
    if (stack->heads[stack->allocations] == NULL) {
        // If we dont have a node at our current head make one.
        stack->heads[stack->allocations] = (AssetNode*) malloc(sizeof(AssetNode));
        stack->tail = stack->heads[stack->allocations];
    } else {
        // We need to allocate memory for the current head->next.
        stack->tail->next = (AssetNode*) malloc(sizeof(AssetNode));
        stack->tail = stack->tail->next;
    }

    // Set the tail's next node to NULL.
    stack->tail->next = NULL;
    AssetNode* node = stack->tail;
    node->asset = (RegisteredAsset*) malloc(sizeof(RegisteredAsset));

    // Set the texture's reference string and check the asset type.
    if (!type_asset(node->asset, asset_path)) {
        ERROR_LOG("Unable to type asset %s.\n", asset_path);
        return false;
    }

    switch (node->asset->type) {
        case Texture:
            node->asset->pointer.texture = IMG_LoadTexture(renderer, asset_path);
            if (node->asset->pointer.texture == NULL) {
                return false;
            }
            break;
        case Font:
            node->asset->pointer.font = TTF_OpenFont(asset_path, 20);
            if (node->asset->pointer.font == NULL) {
                return false;
            }
            break;
        case Sound:
            node->asset->pointer.sound = Mix_LoadWAV(asset_path);
            if (node->asset->pointer.font == NULL) {
                return false;
            }
            break;
        default:
            return false;
    }
    return true;
}

/**
 * Push a chunk of assets onto the asset stack as per provided asset manifest.
 */
bool push_asset_chunk(SDL_Renderer* renderer, AssetStack* stack, const char* manifest) {
    // Check if the file can be opened.
    char asset_path[100];   // Maximum size of provided filename.
    FILE* fp = fopen(manifest, "r");
    if (fp == NULL) {
        return false;
    }

    // Is this the first allocation for the stack?
    if (stack->allocations == -1) {
        stack->heads = (AssetNode**) malloc(sizeof(AssetNode*));
    // Increase the size of the head array.
    } else {
        stack->heads = (AssetNode**) realloc(stack->heads, sizeof(AssetNode*) * (stack->allocations + 1));
    }

    stack->allocations++;
    stack->heads[stack->allocations] = NULL;
    INFO_LOG("Stack allocations: %d\n", stack->allocations);

    // Read each line of the file and add a new node for each loaded asset.
    while(fgets(asset_path, sizeof(asset_path), fp)) {
        int blen = strlen(asset_path);
        if (asset_path[blen - 1] == '\n') {
            asset_path[strlen(asset_path) - 1] = '\0';
        }
        if (!push_asset(renderer, stack, asset_path)) {
            // Unable to load?
            ERROR_LOG("Could not load file: %s\n", asset_path);
        }
        memset(asset_path, '\0', sizeof(asset_path));
    }

    // Close file.
    fclose(fp);
    return true;
}

/**
 * Pop a chunk of the assets from the stack.
 */
bool pop_asset_chunk(AssetStack* stack) {
    // Free all assets from the top most chunk.
    AssetNode* current = stack->heads[stack->allocations];
    while(current != NULL && current->asset != NULL) {
        free_asset(current->asset);
	    free(current->asset);
        AssetNode* temp = current->next;
        free(current);
        current = temp;
        if (current->next == NULL) {
            break;
        }
    }
    // Re-allocate the list of heads.
    INFO_LOG("Stack allocations: %d\n", stack->allocations);
    if (stack->allocations > 1) {
        stack->heads = (AssetNode**) realloc(stack->heads, (stack->allocations + 1) * sizeof(RegisteredAsset*));
        // Set the tail pointer.
        AssetNode* tail = stack->heads[stack->allocations];
        while(tail->next != NULL) {
            tail = tail->next;
        };
    } else {
        // Free all data.
        free(stack->heads);
    }
    stack->allocations--;
    INFO_LOG("Stack allocations: %d\n", stack->allocations);
    return true;
}

/**
 * Free all the assets on the stack.
 */
bool free_asset_stack(AssetStack* stack) {
    while(stack->allocations > 0) {
        pop_asset_chunk(stack);
    }
    return true;
}

/**
 * If an asset is found with provided reference, return pointer to asset, else return NULL.
 */
RegisteredAsset* get_asset_by_ref(const char* reference, int chunk) {
    // If the provided chunk is out of our range we return NULL.
    if (chunk < 0 || chunk > gameData.assets.allocations) {
        return NULL;
    }
    AssetNode* node = gameData.assets.heads[chunk];
    while (node != NULL) {
        if (strcmp(node->asset->reference, reference) == 0) {
            return (RegisteredAsset*) node->asset;
	    }
        node = node->next;
    }
    return NULL;
}

/**
 * Linearly traverse the stack for debug purposes.
 */
void debug_asset_stack(AssetStack stack) {
    INFO_LOG("Debugging stack.\n");
    INFO_LOG("Allocations: %d\n", stack.allocations);
    if (stack.heads[0] == NULL) {
        INFO_LOG("We don't have a head..\n");
	return;
    }
    INFO_LOG("We have a head!\n");
    AssetNode* start = stack.heads[0];
    while (start != NULL) {
	INFO_LOG("Texture: %s\n", start->asset->reference);
        start = start->next;
    }
}

