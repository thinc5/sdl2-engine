#ifndef ASSETSTACK_H
#define ASSETSTACK_H

#include <stdint.h>

#include "asset.h"

/**********************************************************************
 * A stack based implementation for loading assets that uses a linked list.
 *********************************************************************/

/**
 * The node containing an asset.
 */
typedef struct AssetNode {
    RegisteredAsset* asset;
    struct AssetNode* next;
} AssetNode;

/**
 * The stack holding our assets.
 */
typedef struct AssetStack {
    int16_t allocations;
    AssetNode** heads;
    AssetNode* tail;
} AssetStack;

/**
 * Initialize the asset stack.
 */
bool init_asset_stack(AssetStack* stack);

/**
 * Push a chunk of assets onto the asset stack as per provided asset manifest.
 */
bool push_asset_chunk(SDL_Renderer* renderer, AssetStack* stack, const char* manifest);

/**
 * Pop a chunk of the assets from the stack.
 */
bool pop_asset_chunk(AssetStack* stack);

/**
 * Free all the assets on the stack.
 */
bool free_asset_stack(AssetStack* stack);

/**
 * If an asset is found with provided reference, return pointer to asset, else return NULL.
 */
RegisteredAsset* get_asset_by_ref(const char* reference, int chunk);

/**
 * Linearly traverse the stack for debug purposes.
 */
void debug_asset_stack(AssetStack stack);

#endif

