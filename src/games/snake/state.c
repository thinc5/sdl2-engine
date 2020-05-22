#include <SDL2/SDL.h>

#include <stdint.h>

#include "../../../include/debug.h"
#include "../../../include/game.h"
#include "../../../include/rendering/renderertemplates.h"
#include "../../../include/entities/entity.h"
#include "../../../include/games/snake/state.h"

/**
 * Render the state of the cat debug scene.
 */
static void render_snake_state(void* e) {
    // Get font and the UI entity.
    TTF_Font* font = get_asset_by_ref("ssp-regular.otf", 0)->pointer.font;
    Entity* entity = (Entity*) e;
    SDL_Color c = {255, 255, 255};
    SDL_Rect pos = entity->position;
    // Cast as SnakeStateS.
    SnakeState* state = gameData.scene->state;
    char time[15];
    uint32_t remaining_time = (int) (state->remaining_time / 1000);
    sprintf(time, "Time: %4u", remaining_time);
    render_font(font, &pos, c, time);
    pos.y += 50;
    char score[15];
    uint32_t current_score = state->score;
    sprintf(score, "Score: %4u", current_score);
    render_font(font, &pos, c, score);
}

/**
 * Update game state timer.
 */
static void snake_state_on_tick(void) {
    // Cast as SnakeState.
    SnakeState* state = (SnakeState*) gameData.scene->state;
    // Have we run out of time?
    int32_t remaining = state->remaining_time - (SDL_GetTicks() - state->last_time);
    // INFO_LOG("Remaining time: %d\n", remaining);
    if (remaining < 0) {
        // Load main menu.
        change_scene(NULL);
        return;
    }
    // Decrease timer.
    state->remaining_time -= SDL_GetTicks() - state->last_time;
    state->last_time = SDL_GetTicks();
}

/**
 * Initialize the game of Snake.
 */
Entity init_snake_state(void) {
    Entity snake_state;
    // Load cat assets make more flexable and specific later.
    if (!init_entity(&snake_state, NULL, NULL)) {
        ERROR_LOG("Could not initialize cat state entity.\n");
        return (Entity) { 0 };
    }
    // Load cat components.
    snake_state.components[OnTick].call = &snake_state_on_tick;
    snake_state.components[Render].call = &render_snake_state;
    return snake_state;
}
