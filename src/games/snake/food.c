#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdint.h>

#include "../../../include/config.h"
#include "../../../include/debug.h"
#include "../../../include/game.h"
#include "../../../include/games/snake/state.h"
#include "../../../include/components/move.h"
#include "../../../include/entities/entity.h"
#include "../../../include/rendering/renderertemplates.h"
#include "../../../include/util/camera.h"

#include "../../../include/games/snake/food.h"

/**
 * Spawn a piece of food.
 */
void spawn_food(uint32_t lifetime, uint16_t score) {
    SnakeState* state = (SnakeState*) gameData.scene->state;
    for (int pos = 0; pos < MAX_FOOD; pos++) {
        Food food = state->food[pos];
        if (food.lifetime == 0) {
            // Generate random food location

            food.lifetime = lifetime;
            food.score = score;
            // Insert into the array.
            state->food[pos] = food;
        }
    }
}

/**
 * Render all pieces of food.
 */
void render_food() {
    SnakeState* state = (SnakeState*) gameData.scene->state;
    SDL_Colour colour = { 0, 0, 255 };
    SDL_Rect board = transform_rect((SDL_Rect) { 0 }, 0.0f, 0.0f, 1.6f, 1.6f);
    float gridWidth = board.w / state->grid.x;
    float gridHeight = board.h / state->grid.y;
    // Get the first food piece.
    for (int pos = 0; pos < MAX_FOOD; pos++) {
        Food food = state->food[pos];
        if (food.lifetime == 0) {
            continue;
        }
        SDL_Rect target = {
            .w = gridWidth,
            .h = gridHeight,
            .x = board.x + (gridWidth * food.x),
            .y = board.y + (gridHeight * food.y)
        };
        render_rectangle(&target, colour, true);
    }
}

/**
 * Initializes the snake food.
 */
Entity init_food(void) {
    Entity food;
    // Load snake assets.
    if (!init_entity(&food, NULL, NULL)) {
        ERROR_LOG("Could not initialize snake entity.\n");
        return (Entity) { 0 };
    }
    // Load cat components.
    food.timers[0] = init_timer();
    food.components[Render].call = &render_food;
    return food;
}
