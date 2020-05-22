#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/debug.h"
#include "../../../include/game.h"
#include "../../../include/managers/assetmanager.h"
#include "../../../include/managers/entitymanager.h"
#include "../../../include/managers/eventmanager.h"
#include "../../../include/scenes/scene.h"
#include "../../../include/util/camera.h"

#include "../../../include/games/snake/state.h"
#include "../../../include/games/snake/ui.h"
#include "../../../include/games/snake/grid.h"
#include "../../../include/games/snake/snake.h"
#include "../../../include/games/snake/food.h"

/**
 * Process snake specific events.
 */
static void snake_handler() {
    SnakeState* state = (SnakeState*) gameData.scene->state;
    switch (gameData.event.key.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_a:
            // Implement after we have selection.
            state->snake.dir = LEFT;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            state->snake.dir = RIGHT;
            break;
        case SDLK_UP:
        case SDLK_w:
            state->snake.dir = UP;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            state->snake.dir = DOWN;
            break;
        default:
            default_handler();
    }
}

/**
 * Constructor for the debug testing scene.
 */
void init_snake_scene(void) {
    if (!init_scene(gameData.scene)) {
        gameData.scene = NULL;
        return;
    }
    memcpy(&gameData.scene->title, "Snake Game", 12);

    // Load assets for the debug scene.
    if (!push_asset_chunk(gameData.renderer, &gameData.assets,
                "./res/snake.manifest")) {
        free_scene(gameData.scene);
        gameData.scene = NULL;
        return;
    }

    // Scene features.
    gameData.scene->event_handler = &snake_handler;
    gameData.scene->type = Debug;
    
    // Init state.
    gameData.scene->state = (void*) malloc(sizeof(SnakeState));
    SnakeState* state = (SnakeState*) gameData.scene->state;
    state->score = 0;
    state->starting_time = SDL_GetTicks();
    state->duration = 0;
    state->game_speed = 1000;
    // Init grid
    state->grid.x = 20;
    state->grid.y = 20;
    // Init snake
    state->snake.size = 1;
    state->snake.sections[0].x = 0;
    state->snake.sections[0].y = 0;

    // Add entities.
    // Create grid.
    add_entity(&gameData.scene->entities, &init_snake_grid, (SDL_Rect) { 0 });
    // Create snake.
    add_entity(&gameData.scene->entities, &init_snake, (SDL_Rect) { 0 });
    // Create UI.
    add_entity(&gameData.scene->entities, &init_snake_ui,
            transform_rect((SDL_Rect) { 0 }, 0.9f, 0.9f, 0.2f, 0.1f)); 
}
