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

/**
 * Constructor for the debug testing scene.
 */
void init_snake_scene(void) {
    if (!init_scene(gameData.scene)) {
        gameData.scene = NULL;
        return;
    }
    memcpy(&gameData.scene->title, "Snake Scene", 12);

    // Load assets for the debug scene.
    if (!push_asset_chunk(gameData.renderer, &gameData.assets,
                "./res/debug.manifest")) {
        free_scene(gameData.scene);
        gameData.scene = NULL;
        return;
    }
    
    // Populate scene with entities.
    
    gameData.scene->bg = get_asset_by_ref("cat3.jpg", 0)->pointer.texture;
    gameData.scene->cursor = get_asset_by_ref("cursor.png", 1)->pointer.texture;
    gameData.scene->event_handler = &default_handler;
    gameData.scene->type = Debug;
    
    // Init state.
    gameData.scene->state = (void*) malloc(sizeof(SnakeState));
    SnakeState* state = (SnakeState*) gameData.scene->state;
    state->remaining_time = 10 * 1000;  // 60 Seconds..
    state->score = 0;
    state->last_time = SDL_GetTicks();
    add_entity(&gameData.scene->entities, &init_snake_state,
            transform_rect((SDL_Rect) { 0 }, 0.2f, 0.2f, 0.1f, 0.1f));
}
