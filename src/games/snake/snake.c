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
            .x = board.x + (gridWidth * state->snake.sections[section].x),
            .y = board.y + (gridHeight * state->snake.sections[section].y)
        };
        render_rectangle(&target, colour, true);
    }
}

/**
 * Actually move the snake.
 */
static void move_snake(void* e) {
    // Entity* entity = (Entity*) e;
    SnakeState* state = (SnakeState*) gameData.scene->state;
    // Move other parts.
    for (int section = 0; section < state->snake.size - 1; section++) {
        state->snake.sections[section + 1].x = state->snake.sections[section].x;
        state->snake.sections[section + 1].y = state->snake.sections[section].y;
    }
    switch (state->snake.dir) {
        case LEFT:
            if (state->snake.sections[0].x - 1 >= 0) {
                state->snake.sections[0].x = state->snake.sections[0].x - 1;
            } else {
                state->snake.sections[0].x = state->grid.x - 1;
            }
            break;
        case RIGHT:
            if (state->snake.sections[0].x + 1 < state->grid.x) {
                state->snake.sections[0].x = state->snake.sections[0].x + 1;
            } else {
                state->snake.sections[0].x = 0;
            }
            break;
        case UP:
            if (state->snake.sections[0].y - 1 >= 0) {
                state->snake.sections[0].y = state->snake.sections[0].y - 1;
            } else {
                state->snake.sections[0].y = state->grid.y - 1;
            }
            break;
        case DOWN:
            if (state->snake.sections[0].y + 1 < state->grid.y) {
                state->snake.sections[0].y = state->snake.sections[0].y + 1;
            } else {
                state->snake.sections[0].y = 0;
            }
            break;
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
        move_snake(snake);
        // Reset the timer.
        snake->timers[0].startTime = SDL_GetTicks();
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
