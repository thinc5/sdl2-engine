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
    // Swap colour of button
    SDL_Texture* temp = entity->textures[0];
    entity->textures[0] = entity->textures[1];
    entity->textures[1] = temp;
    Mix_PlayChannel(-1, entity->sounds[0], 0);
}

/**
 * Initilizes the cat entity and its components.
 */
Entity initButton(AssetRegistry* reg) {
    Entity entity;
    if (!initEntity(&entity, reg, "click.png", "click1.ogg")) {
        fprintf(stderr, "Could not initilize button entity.\n");
        return (Entity) { 0 };
    }
    entity.textures[1] = getAssetByReference("unclick.png", reg)->pointer.texture;
    // Starting position
    entity.position.x = 200;
    entity.position.y = 200;
    // Width and height
    entity.position.w = 100;
    entity.position.h = 50;
    // Load custom components.
    entity.components[LeftClicked].call = &buttonLeftClicked;
    return entity;
}

