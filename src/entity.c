#include <stdio.h>
#include <stdbool.h>

#include "../include/entity.h"
#include "../include/assetmanager.h"

/**
 * Initalize an entity with a default size, location and with provided texture and sound.
 */
bool initEntity(Entity* e, AssetRegistry* reg, const char* textureRef, const char* soundRef) {
    if (textureRef != NULL) {
        RegisteredAsset* asset = getAssetByReference(textureRef, reg);
        if (asset == NULL) {
            fprintf(stderr, "Unable to find asset for entity: %s\n", textureRef);
            return false;
        }
        e->texture = asset->pointer.texture;
    }
    if (soundRef != NULL) {
        RegisteredAsset* asset = getAssetByReference(soundRef, reg);
        if (asset == NULL) {
            fprintf(stderr, "Unable to find asset for entity: %s\n", soundRef);
            return false;
        }
        e->sound = asset->pointer.sound;
    }
    e->remove = false;
    return true;
}

