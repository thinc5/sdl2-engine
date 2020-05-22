#include <SDL2/SDL.h>

#include "../../../include/debug.h"
#include "../../../include/rendering/renderertemplates.h"
#include "../../../include/games/snake/scene.h"
#include "../../../include/entities/entity.h"
#include "../../../include/games/snake/snakebutton.h"

/**
 * Behaviour of button when left clicked.
 */
static void button_left_clicked(void* e) {
    change_scene(&init_snake_scene);
}

/**
 * Initializes the cat entity and its components.
 */
static Entity init_button(void) {
    Entity entity;
    if (!init_entity(&entity, NULL, NULL)) {
        ERROR_LOG("Could not initialize button entity.\n");
        return (Entity) { 0 };
    }
    entity.font = get_asset_by_ref("ssp-regular.otf", 0)->pointer.font;
    // Load custom components.
    entity.components[LeftClicked].call = &button_left_clicked;
    return entity;
}

/**
 * Override the render function to show the label.
 */
static void snake_button_render(void* e) {
    Entity* entity = (Entity*) e;
    SDL_Color c = {255, 255, 0};
    render_rectangle(&entity->position, c, true);
    c = (SDL_Color) { .r = 255,  .g = 255, .b = 255};
    render_font(entity->font, &entity->position, c, "Play Snake!");
}

/**
 * Button to load the snake game.
 */
Entity init_snake_button(void) {
    Entity entity = init_button();
    entity.components[Render].call = &snake_button_render;
    return entity;
}
