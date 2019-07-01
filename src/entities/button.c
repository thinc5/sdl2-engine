#include <SDL2/SDL_mixer.h>

#include <stdio.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/scenes/scene.h"
#include "../../include/scenes/debugscene.h"
#include "../../include/entities/entity.h"
#include "../../include/components/component.h"
#include "../../include/entities/button.h"

/**
 * Behaviour of button when left clicked.
 */
static void button_left_clicked(void* e) {
    Entity* entity = (Entity*) e;
    // Swap colour of button
    SDL_Texture* temp = entity->textures[0];
    entity->textures[0] = entity->textures[1];
    entity->textures[1] = temp;
    // Play click sound
    Mix_PlayChannel(-1, entity->sounds[0], 0);
    // Load target.
    change_scene(&init_debug_scene);
}

/**
 * Initializes the cat entity and its components.
 */
Entity init_button(AssetStack* stack) {
    Entity entity;
    if (!init_entity(&entity, stack, "click.png", "click1.ogg")) {
        ERROR_LOG("Could not initialize button entity.\n");
        return (Entity) { 0 };
    }
    entity.textures[1] = get_asset_by_ref("unclick.png", stack, 0)->pointer.texture;
    // Load custom components.
    entity.components[LeftClicked].call = &button_left_clicked;
    return entity;
}

