#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdbool.h>

#include "../include/entity.h"
#include "../include/component.h"
#include "../include/assetmanager.h"
#include "../include/renderertemplates.h"

/**
 * Defualt deleted component call for all entites.
 */
void deleted(void* e) {
    printf("Entity deleted!\n");
    Entity* entity = (Entity*) e;
    entity->remove = true;
}

/**
 * Defualt render call for all entites.
 */
void render(void* e, SDL_Renderer* r) {
    Entity* entity = (Entity*) e;
    renderTexture(r, entity->texture, &entity->position);
}

/**
 * Returns true if the entity has queried component.
 */
bool hasComponent(Entity* e, ComponentType c) {
    return !(e->components[c].call == NULL);
}

/**
 * Initalize an entity with a default size, location and with provided texture and sound.
 */
bool initEntity(Entity* e, AssetRegistry* reg, const char* textureRef, const char* soundRef) {
    // Initilise all calls as null
    for (int i = 0; i < COMPONENT_TOTAL; i++) {
        e->components[i].call = NULL;
    }
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
    e->components[Deleted].call = &deleted;
    e->components[Render].call = &render;
    return true;
}

