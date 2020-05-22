#include <stdlib.h>
#include <string.h>

#include "../../include/config.h"
#include "../../include/debug.h"
#include "../../include/managers/asset.h"
#include "../../include/managers/assetstack.h"
#include "../../include/game.h"

/****************************************************************************
 * A stack based implementation for loading assets that uses a linked list. *
 ****************************************************************************/

#ifdef DEBUG
/**
 * Linearly traverse the stack for debug purposes.
 */
static void debug_asset_stack(AssetStack* stack) {
    DEBUG_LOG("-- Debugging stack --\n");
    DEBUG_LOG("Allocations: %d\n", stack->allocations + 1);
    if (stack->allocations < 0 && stack && stack->heads) {
        DEBUG_LOG("We don't have a head..\n");
	    return;
    }
    DEBUG_LOG("We have a head at: %lu\n", (unsigned long) stack->heads[0]);
    AssetNode* start = stack->heads[0];
    int assets = 0;
    while (start) {
	    DEBUG_LOG("Asset %d ---\n", assets);
        if (!start || !start->asset) {
            DEBUG_LOG("Asset has no asset data...\n");
            continue;
        }
        if (start->asset || start->asset->reference) {
            DEBUG_LOG("Path %s\n", start->asset->reference);\
        }
        if (start->asset || start->asset->pointer.pointer) {
            DEBUG_LOG("Pointer %p\n", (void*) start->asset->pointer.pointer);
        }
        if (start->next) {
            DEBUG_LOG("Next %p\n", (void*) start->next);
        }
        start = start->next;
        assets++;
    }
    DEBUG_LOG("Assets found: %d\n", assets);
    DEBUG_LOG("-- Debugged stack --\n");
}
#endif

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
 * Push an asset onto the stack.
 */
static bool push_asset(SDL_Renderer* renderer, AssetStack* stack, const char* asset_path) {
    // We are always working with the current tail of the AssetStack, pushing to the end.
    if (!stack || !stack->tail) {
        ERROR_LOG("Could not find a valid stack or the tail was NULL\n");
        return false;
    }
    
    AssetNode* node = stack->tail;
    // Set the next node to NULL.
    node->next = NULL;
    // Allocate space for the asset.
    node->asset = (RegisteredAsset*) malloc(sizeof(RegisteredAsset));

    // Set the texture's reference string and check the asset type (using filename for
    // now, not header of file itself. Also copies the filename into AssetNode).
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
    DEBUG_LOG("Loaded asset (%s): %s.\n", AssetTypeValue[node->asset->type],
            node->asset->reference);
    return true;
}

/**
 * Push a chunk of assets onto the asset stack as per asset manifest.
 */
bool push_asset_chunk(SDL_Renderer* renderer, AssetStack* stack, const char* manifest) {
    DEBUG_LOG("Pushing asset stack from manifest: %s\n", manifest);
    // Check if the file can be opened.
    FILE* fp = fopen(manifest, "r");
    if (fp == NULL) {
        return false;
    }

    // Is this the first allocation for the stack?
    if (stack->allocations == -1) {
        // Create the head array.
        stack->heads = (AssetNode**) malloc(sizeof(AssetNode*));
    } else if  (stack->allocations >= 0) {
        // Expand the head array.
        stack->heads = (AssetNode**) realloc(stack->heads, sizeof(AssetNode*)
                * (stack->allocations + 1));
    }
    stack->allocations++;
    // Set the tail (the starting location!)
    stack->tail = NULL;
    
    bool first = true;
    DEBUG_LOG("Stack allocations: %d\n", stack->allocations + 1);
    char asset_path[FILENAME_MAX_SIZE]; // Maximum size of provided filename.
    // Read each line of the file and add a new node for each loaded asset.
    while(fgets(asset_path, sizeof(asset_path), fp)) {
        // Prepare filepath.
        int blen = strlen(asset_path);
        if (asset_path[blen - 1] == '\n') {
            asset_path[strlen(asset_path) - 1] = '\0';
        }
        AssetNode* new_node = (AssetNode*) malloc(sizeof(AssetNode));
        // Set the head value.
        if (first) {
            stack->heads[stack->allocations] = new_node;
            DEBUG_LOG("New head at: %lu\n", (unsigned long) new_node);
            first = false;
        }
        // We need to allocate memory for the current head.
        if (stack->tail != NULL && stack->tail->next == NULL) {
            stack->tail->next = (void*) new_node;
        }
        stack->tail = new_node;
        stack->tail->next = NULL;        
        
        // Load and register asset.
        stack->tail->asset = (RegisteredAsset*) malloc(sizeof(RegisteredAsset));
        if (!push_asset(renderer, stack, asset_path)) {
            // Unable to load?
            ERROR_LOG("Could not load file: %s\n", asset_path);
            free(stack->tail->asset->reference);
            free(stack->tail->asset);
            free(stack->tail);
        }

        // Clean buffer for next run.
        memset(asset_path, '\0', sizeof(asset_path));
    }

    // Close file.
    fclose(fp);
    for (int i = 0; i < stack->allocations + 1; i++) {
        DEBUG_LOG("head: %lu\n", (unsigned long) stack->heads[i]);
    }
    
    #ifdef DEBUG
    debug_asset_stack(stack);
    #endif
    return true;
}

/**
 * Pop (free) a chunk of the assets from the stack.
 */
bool pop_asset_chunk(AssetStack* stack) {
    // Is there anything left to free?
    DEBUG_LOG("Current chunks: %d\n", stack->allocations + 1);
    if (stack->allocations < 0) {
        ERROR_LOG("Tried to free a chunk (%d) when there were none remaining.\n",
                stack->allocations);
        return false;
    }
    
    // Free all assets from the top most chunk.
    DEBUG_LOG("Free head: %lu\n", (unsigned long) stack->heads[stack->allocations]);
    AssetNode* current = stack->heads[stack->allocations];
    while(current != NULL && current->asset != NULL) {
        DEBUG_LOG("Freeing asset (%s): \"%s\" from chunk %d (%lu)\n",
                AssetTypeValue[current->asset->type],
                current->asset->reference, stack->allocations + 1,
                (unsigned long) current->asset->pointer.texture);
        free_asset(current->asset);
        // Free the RegisteredAsset.
	    free(current->asset);
        // Get the pointer to the next asset.
        current->asset = NULL;
        AssetNode* temp = current->next;
        // Free the AssetNode.
        free(current);
        // Set our temp as our next asset.
        current = temp;
    }

    // Re-allocate/free the list of heads.
    if (stack->allocations > 0) {
        stack->heads = (AssetNode**) realloc(stack->heads, (stack->allocations + 1)
                * sizeof(AssetNode*));

        // Set the tail pointer.
        stack->tail = stack->heads[stack->allocations];
    } else {
        // Free list of heads.
        free(stack->heads);
        stack->heads = NULL;
        stack->tail = NULL;
    }
    stack->allocations--;
    DEBUG_LOG("Remaining chunks: %d\n", stack->allocations + 1);
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
 * If an asset is found with provided reference, return pointer to asset,
 * else, return NULL.
 */
RegisteredAsset* get_asset_by_ref(const char* reference, int chunk) {
    DEBUG_LOG("Looking for %s in chunk %d\n", reference, chunk);
    // If the provided chunk is out of our range we return NULL.
    if (chunk < 0 || chunk > gameData.assets.allocations + 1) {
        ERROR_LOG("Provided chunk is outside of range: %d\n", chunk);
        return NULL;
    }
    AssetNode* node = gameData.assets.heads[chunk];
    while (node != NULL) {
        if (strcmp(node->asset->reference, reference) == 0) {
            DEBUG_LOG("Found %s\n", reference);
            return (RegisteredAsset*) node->asset;
	    }
        node = node->next;
    }
    ERROR_LOG("Unable to find specified asset: %s in chunk %d\n",
            reference, chunk);
    return NULL;
}

