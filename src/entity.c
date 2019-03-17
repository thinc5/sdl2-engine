#include <stdio.h>
#include <stdbool.h>

#include "../include/entity.h"
#include "../include/assetmanager.h"

/**
 * Initalize an entity with a default size, location and with provided texture.
 */
bool initEntity(Entity* e, AssetRegistry* reg, const char* textureRef) {
    RegisteredAsset* asset = getAssetByReference(textureRef, reg);
    if (asset == NULL) {
        fprintf(stderr, "Unable to find asset for entity: %s\n", textureRef);
        return false;
    }
    e->texture = asset->pointer.texture;
    e->position.x = 50;
    e->position.y = 50;
    e->position.w = 50;
    e->position.h = 50;
    e->move = &move;
    return true;
}

/**
 * Move an entity a set distance in a provided direction.
 */
void move(void* e, Direction d) {
    Entity* entity = (Entity*) e;
    switch (d) {
        case UP:
            entity->position.y -= 50;
            break;
        case DOWN:
            entity->position.y += 50;
            break;
        case LEFT:
            entity->position.x -= 50;
            break;
        case RIGHT:
            entity->position.x += 50;
            break;
        default:
            break;
    }
}