#include <SDL2/SDL.h>

#include <stdint.h>

#include "../../../include/debug.h"
#include "../../../include/game.h"
#include "../../../include/rendering/renderertemplates.h"
#include "../../../include/entities/entity.h"
#include "../../../include/util/camera.h"

#include "../../../include/games/snake/state.h"

/**
 * Render the snake game ui.
 */
static void render_ui(void* e) {
    // Get font and the UI entity.
    Entity* entity = (Entity*) e;
    SDL_Color c = {0, 255, 255, 255};
    SDL_Rect pos = entity->position;

    // Cast as SnakeState.
    SnakeState* state = gameData.scene->state;
    
    // Show elapsed time.
    char time[15];
    sprintf(time, "Time: %4u", state->duration);
    render_font(entity->font, &pos, c, time);
    
    // Show player score.
    pos.y += 50;
    char score[15];
    uint32_t current_score = state->score;
    sprintf(score, "Score: %4u", current_score);
    render_font(entity->font, &pos, c, score);
}

/**
 * Update game state.
 */
static void state_on_tick(void) {
    // Cast as SnakeState.
    SnakeState* state = (SnakeState*) gameData.scene->state;
    // Calculate duration.
    state->duration = (uint32_t) (SDL_GetTicks() - state->starting_time) / 1000;
}

/**
 * Initialize the game of Snake.
 */
Entity init_snake_ui(void) {
    Entity snake_state;
    // Load cat assets make more flexable and specific later.
    if (!init_entity(&snake_state, NULL, NULL)) {
        ERROR_LOG("Could not initialize cat state entity.\n");
        return (Entity) { 0 };
    }
    snake_state.font = get_asset_by_ref("ssp-regular.otf", 0)->pointer.font;
    // Load cat components.
    snake_state.components[OnTick].call = &state_on_tick;
    snake_state.components[Render].call = &render_ui;
    return snake_state;
}
