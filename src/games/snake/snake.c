#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../../include/config.h"
#include "../../../include/debug.h"
#include "../../../include/game.h"
#include "../../../include/games/snake/state.h"
#include "../../../include/components/move.h"
#include "../../../include/entities/entity.h"
#include "../../../include/rendering/renderertemplates.h"
#include "../../../include/util/camera.h"

#include "../../../include/games/snake/snake.h"

/**
 * Render the snake.
 */
static void render_snake(void* e) {
    SnakeState* state = (SnakeState*) gameData.scene->state;
    SDL_Colour colour = { 0, 0, 255 };
    SDL_Rect board = transform_rect((SDL_Rect) { 0 }, 0.0f, 0.0f, 1.6f, 1.6f);
    float gridWidth = board.w / state->grid.x;
    float gridHeight = board.h / state->grid.y;
    for (int section = 0; section < state->snake.size; section++) {
        SDL_Rect target = {
            .w = gridWidth,
            .h = gridHeight,
            .x = board.x + (gridWidth * state->snake.x),
            .y = board.y + (gridHeight * state->snake.y)
        };
        render_rectangle(&target, colour, true);
    }
}

/**
 * On tick.
 * Limit time via a local timer initialized using a static variable.
 */
static void snake_on_tick(void* e) {
    SnakeState* state = (SnakeState*) gameData.scene->state;
    Entity* snake = (Entity*) e;
    if (!snake->timers[0].started) {
        start_timer(&snake->timers[0]);
    }
    if (time_elapsed(&snake->timers[0], state->game_speed)) {
        // Pick which direction we are moving.
        snake->components[Moved].call(snake);
    }
}

static void move_snake(void* e) {
    // Entity* entity = (Entity*) e;
    SnakeState* state = (SnakeState*) gameData.scene->state;
    switch (state->snake.dir) {
        case LEFT:
            if (state->snake.x - 1 >= 0) {
                state->snake.x = state->snake.x - 1;
            } else {
                state->snake.x = state->grid.x;
            }
            break;
        case RIGHT:
            if (state->snake.x + 1 < state->grid.x) {
                state->snake.x = state->snake.x + 1;
            } else {
                state->snake.x = 0;
            }
            break;
        case UP:
            if (state->snake.y + 1 < state->grid.y) {
                state->snake.y = state->snake.y + 1;
            } else {
                state->snake.y = 0;
            }
            break;
        case DOWN:
            if (state->snake.y - 1 < 0) {
                state->snake.y = state->snake.y - 1;
            } else {
                state->snake.y = state->grid.y;
            }
            break;
    }
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
    snake.components[Render].call = &render_snake;
    return snake;
}
