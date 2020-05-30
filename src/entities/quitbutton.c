#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/scenes/scene.h"
#include "../../include/entities/entity.h"
#include "../../include/components/component.h"
#include "../../include/rendering/renderertemplates.h"
#include "../../include/entities/quitbutton.h"

/**
 * Behaviour of button when left clicked.
 */
static void button_left_clicked(void* e) {
    gameData.status = CLOSING;
}

/**
 * Override the render function to show the label.
 */
static void render(void* e) {
    Entity* entity = (Entity*) e;
    SDL_Color c = { 255, 0, 0, 255 };
    render_rectangle(&entity->position, c, true);
    c = (SDL_Color) { 255, 255, 255, 255 };
    render_font(entity->font, &entity->position, c, "Quit Game");
}

/**
 * Initializes the cat entity and its components.
 */
Entity init_quit_button(void) {
    // Load defaults.
    Entity entity;
    init_entity(&entity, NULL, NULL);
    // Fetch required resources.
    entity.font = get_asset_by_ref("ssp-regular.otf", 0)->pointer.font;
    // Load custom components.
    entity.components[Render].call = &render;
    entity.components[LeftClicked].call = &button_left_clicked;
    return entity;
}
