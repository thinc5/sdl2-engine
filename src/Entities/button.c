#include <SDL2/SDL_mixer.h>

#include <stdio.h>

#include "../../include/entity.h"
#include "../../include/component.h"
#include "../../include/Entities/button.h"

/**
 * Behaviour of button when left clicked.
 */
void buttonLeftClicked(void* e) {
    Entity* entity = (Entity*) e;
    // e->texture = getAssetByReference("", reg).pointer.texture;
    Mix_PlayChannel(-1, entity->sound, 0);
}

/**
 * Initilizes the cat entity and its components.
 */
Entity initButton(AssetRegistry* reg) {
    Entity entity;
    // Load cat assets make more flexable and specific later.
    if (!initEntity(&entity, reg, "click.png", "click1.ogg")) {
        fprintf(stderr, "Could not initilize button entity.\n");
        return (Entity) {};
    }
    // Cat specific specifiations
    // Starting position
    entity.position.x = 200;
    entity.position.y = 200;
    // Width and height
    entity.position.w = 100;
    entity.position.h = 50;
    // Load cat components.
    entity.components[LeftClicked].call = &buttonLeftClicked;
    return entity;
}

