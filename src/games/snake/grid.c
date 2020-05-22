#include <SDL2/SDL.h>

#include <stdint.h>

#include "../../../include/debug.h"
#include "../../../include/game.h"
#include "../../../include/rendering/renderertemplates.h"
#include "../../../include/entities/entity.h"
#include "../../../include/util/camera.h"

#include "../../../include/games/snake/state.h"

/**
 * Render the game board.
 */
static void render_grid(void* e) {
    SDL_Color colour = (SDL_Color) { 0, 0, 0 };
    SnakeState* state = (SnakeState*) gameData.scene->state;
    SDL_Rect board = transform_rect((SDL_Rect) { 0 }, 0.0f, 0.0f, 1.6f, 1.6f);
    float gridWidth = board.w / state->grid.x;
    float gridHeight = board.h / state->grid.y;
    // render_rectangle(&board, (SDL_Color) { 0, 0, 0 }, false);
    for (int x = 0; x < state->grid.x; x++) {
        for (int y = 0; y < state->grid.y; y++) {
            SDL_Rect target = {
                .w = gridWidth,
                .h = gridHeight,
                .x = board.x + (gridWidth * x),
                .y = board.y + (gridHeight * y)
            };
            render_rectangle(&target, colour, false);
        }
    }
    
}

/**
 * Initialize the game of Snake.
 */
Entity init_snake_grid(void) {
    Entity grid;
    // Load cat assets make more flexable and specific later.
    if (!init_entity(&grid, NULL, NULL)) {
        ERROR_LOG("Could not initialize cat state entity.\n");
        return (Entity) { 0 };
    }
    // Load cat components.
    grid.components[Render].call = &render_grid;
    return grid;
}
