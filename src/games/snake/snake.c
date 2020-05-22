#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../../include/config.h"
#include "../../../include/debug.h"
#include "../../../include/game.h"
#include "../../../include/games/snake/state.h"
#include "../../../include/components/move.h"
#include "../../../include/entities/entity.h"
#include "../../../include/games/snake/snake.h"

/**
 * On tick.
 * Limit time via a local timer initialized using a static variable.
 */
static void snake_on_tick(void* e) {
    Entity* entity = (Entity*) e;
    if (!entity->timers[0].started) {
        start_timer(&entity->timers[0]);
    }
    if (time_elapsed(&entity->timers[0], 100)) {
        // Pick which direction we are moving.
        entity->components[Moved].call(entity);
        entity->timers[0].startTime = SDL_GetTicks();
    }
}

static void move_snake(void* e) {
    Entity* entity = (Entity*) e;
    SnakeState* state = (SnakeState*) gameData.scene->state;
    move(entity, state->snake_dir, state->game_speed, (SDL_Rect) { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
}

/**
 * Initializes the snake entity.
 */
Entity init_snake(void) {
    Entity snake;
    // Load snake assets.
    if (!init_entity(&snake, NULL, NULL)) {
        ERROR_LOG("Could not initialize snake entity.\n");
        return (Entity) { 0 };
    }
    // Load cat components.
    snake.timers[0] = init_timer();
    snake.components[Moved].call = &move_snake;
    snake.components[OnTick].call = &snake_on_tick;
    return snake;
}
