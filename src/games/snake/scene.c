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
                "./res/debug.manifest")) {
        free_scene(gameData.scene);
        gameData.scene = NULL;
        return;
    }
    
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

    // Add entities.
    // Create grid.
    add_entity(&gameData.scene->entities, &init_snake_grid, (SDL_Rect) { 0 });
    // Create snake.
    // add_entity(&gameData.scene->entities, &init_snake, (SDL_Rect) { 0 });
    // Create UI.
    add_entity(&gameData.scene->entities, &init_snake_ui,
            transform_rect((SDL_Rect) { 0 }, 0.9f, 0.9f, 0.2f, 0.1f));

    // Scene features.
    gameData.scene->event_handler = &default_handler;
    gameData.scene->type = Debug;
}
