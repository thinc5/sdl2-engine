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
    Entity* grid = e;
    SDL_Color colour = (SDL_Color) { 0, 0, 0, 255 };
    SnakeState* state = (SnakeState*) gameData.scene->state;
    // Place the board.
    
    float gridWidth = state->grid.pos.w / state->grid.x;
    float gridHeight = state->grid.pos.h / state->grid.y;
    render_texture(grid->textures[0], &state->grid.pos);
    for (int x = 0; x < state->grid.x; x++) {
        for (int y = 0; y < state->grid.y; y++) {
            SDL_Rect target = {
                .w = gridWidth,
                .h = gridHeight,
                .x = state->grid.pos.x + (gridWidth * x),
                .y = state->grid.pos.y + (gridHeight * y)
            };
            render_rectangle(&target, colour, false);
        }
    }
}

/**
 * Initialize a generic grid.
 */
Entity init_snake_grid(void) {
    Entity grid;
    // Load cat assets make more flexable and specific later.
    if (!init_entity(&grid, "grass.jpg", NULL)) {
        ERROR_LOG("Could not initialize cat state entity.\n");
        return (Entity) { 0 };
    }
    // Load cat components.
    grid.components[Render].call = &render_grid;
    return grid;
}
