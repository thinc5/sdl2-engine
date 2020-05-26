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
    float gridWidth = state->grid.pos.w / state->grid.x;
    float gridHeight = state->grid.pos.h / state->grid.y;
    SDL_Rect target = { .w = gridWidth, .h = gridHeight };
    for (int section = 0; section < state->snake.size; section++) {
        target.x = state->grid.pos.x + (gridWidth * state->snake.sections[section].x);
        target.y = state->grid.pos.y + (gridHeight * state->snake.sections[section].y);
        render_rectangle(&target, colour, true);
    }
}

/**
 * Actually move the snake.
 */
static void dead_snake(SnakeState* state) {
    // Has the head collided with any other part of the snake?
    for (int section = 1; section < state->snake.size - 1; section++) {
        if (state->snake.sections[0].x == state->snake.sections[section].x &&
                state->snake.sections[0].y == state->snake.sections[section].y) {
            // Collision.
            state->status = SNAKE_DEAD;
            return;
        }
    }
}

/**
 * Actually move the snake.
 */
static void move_snake(SnakeState* state) {
    // Move other segments.
    for (int section = state->snake.size - 1; section > 0; section--) {
        // They are equal to their predecessors' location.
        state->snake.sections[section].x = state->snake.sections[section - 1].x;
        state->snake.sections[section].y = state->snake.sections[section - 1].y;
    }
    // Move head.
    switch (state->snake.next_dir) {
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
        case DIRECTIONS:
        default:
            break;
    }
    state->snake.dir = state->snake.next_dir;
}

/**
 * Check if the snake gets a snack.
 */
static void eat_food(SnakeState* state) {
    // Snake can only eat from the head :)
    int x = state->snake.sections[0].x;
    int y = state->snake.sections[0].y;
    // Check all the food.
    for (int i = 0; i < MAX_FOOD; i++) {
        if (x == state->food[i].x && y == state->food[i].y) {
            // Add the score.
            state->score = state->score + state->food[i].score;
            // Remove the food.
            state->food[i] = (Food) { 0 };
            // Grow the snake by 1.
            state->snake.sections[state->snake.size] = state->snake.sections[state->snake.size - 1];
            state->snake.size++;
        }
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
        // Move the snake.
        move_snake(state);
        // Do we eat food?
        eat_food(state);
        // Do we have game over?
        dead_snake(state);
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
    snake.components[OnTick].call = &snake_on_tick;
    snake.components[Render].call = &render_snake;
    return snake;
}
