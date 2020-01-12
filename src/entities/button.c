#include <SDL2/SDL_mixer.h>

#include <stdio.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/scenes/scene.h"
#include "../../include/scenes/debugscene.h"
#include "../../include/entities/entity.h"
#include "../../include/components/component.h"
#include "../../include/entities/button.h"
#include "../../include/rendering/renderertemplates.h"

/**
 * Behaviour of button when left clicked.
 */
static void button_left_clicked(void* e) {
    change_scene(&init_debug_scene);
}

/**
 * Initializes the cat entity and its components.
 */
Entity init_button(void) {
    Entity entity;
    if (!init_entity(&entity, "click.png", "click1.ogg")) {
        ERROR_LOG("Could not initialize button entity.\n");
        return (Entity) { 0 };
    }
    entity.textures[1] = get_asset_by_ref("unclick.png", 0)->pointer.texture;
    // Load custom components.
    entity.components[LeftClicked].call = &button_left_clicked;
    return entity;
}

/**
 * Override the render function to show the label.
 */
static void play_button_render(void* e) {
    render(e);
    Entity* entity = (Entity*) e;
    SDL_Color c = {255, 0, 0};
    render_font(get_asset_by_ref("ssp-regular.otf", 0)->pointer.font, &entity->position, c, "Play Game!");
}

/**
 * Initializes the cat entity and its components.
 */
Entity init_play_button(void) {
    Entity entity = init_button();
    entity.components[Render].call = &play_button_render;
    return entity;
}

