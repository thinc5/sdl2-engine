#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../../include/debug.h"
#include "../../include/entities/entity.h"
#include "../../include/components/component.h"
#include "../../include/managers/assetstack.h"
#include "../../include/rendering/renderertemplates.h"

/**
 * Default deleted component call for all entities.
 */
void deleted(void* e) {
    Entity* entity = (Entity*) e;
    entity->remove = true;
}

/**
 * Default render call for all entities.
 */
void render(void* e, SDL_Renderer* r) {
    Entity* entity = (Entity*) e;
    render_texture(r, entity->textures[0], &entity->position);
}

/**
 * Initialize an entity with a default size, location and with provided texture and sound.
 */
bool init_entity(Entity* e, AssetStack* stack, const char* texture, const char* sound) {
    // Initialize all components as null.
    for (int i = 0; i < COMPONENT_TOTAL; i++) {
        e->components[i].call = NULL;
    }
    memset(e->stats, -1, sizeof(int));
    // Grab assets.
    if (texture != NULL) {
        RegisteredAsset* asset = (RegisteredAsset*) get_asset_by_ref(texture, stack, 0);
        if (asset == NULL) {
            INFO_LOG("Unable to find asset for entity: %s\n", texture);
            return false;
        }
        e->textures[0] = asset->pointer.texture;
    }
    if (sound != NULL) {
        RegisteredAsset* asset = (RegisteredAsset*) get_asset_by_ref(sound, stack, 0);
        if (asset == NULL) {
            ERROR_LOG("Unable to find asset for entity: %s\n", sound);
            return false;
        }
        e->sounds[0] = asset->pointer.sound;
    }
    // Set components.
    e->remove = false;
    e->components[Deleted].call = &deleted;
    e->components[Render].call = &render;
    return true;
}

/**
 * Returns true if the entity has queried component.
 */
bool has_component(Entity* e, ComponentType c) {
    return !(e->components[c].call == NULL);
}

