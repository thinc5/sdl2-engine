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
            if (state->snake.dir != RIGHT) {
                state->snake.next_dir = LEFT;
            }
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            if (state->snake.dir != LEFT) {
                state->snake.next_dir = RIGHT;
            }
            break;
        case SDLK_UP:
        case SDLK_w:
            if (state->snake.dir != DOWN) {
                state->snake.next_dir = UP;
            }
            break;
        case SDLK_DOWN:
        case SDLK_s:
            if (state->snake.dir != UP) {
                state->snake.next_dir = DOWN;
            }
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
    state->status = SNAKE_ALIVE;
    state->score = 0;
    state->starting_time = SDL_GetTicks();
    state->duration = 0;
    state->game_speed = 750;
    // Init grid
    state->grid.x = 15;
    state->grid.y = 10;
    state->grid.pos = transform_right_angle_rect((SDL_Rect) { 0 }, 0.0f, 0.0f, 1.7f, 1.7f, state->grid.x, state->grid.y);
    // Init snake
    state->snake.size = 1;
    state->snake.sections[0].x = rand() % state->grid.x;
    state->snake.sections[0].y = rand() % state->grid.y;
    state->snake.next_dir = rand() % DIRECTIONS;

    // Add entities.
    // Create grid.
    add_entity(&gameData.scene->entities, &init_snake_grid, (SDL_Rect) { 0 });
    // Create snake.
    add_entity(&gameData.scene->entities, &init_snake, (SDL_Rect) { 0 });
    // Create food pool.
    add_entity(&gameData.scene->entities, &init_food, (SDL_Rect) { 0 });
    // Create UI.
    add_entity(&gameData.scene->entities, &init_snake_ui,
            transform_rect((SDL_Rect) { 0 }, 0.85f, 0.9f, 0.25f, 0.15f)); 
}
