#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/managers/assetstack.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/managers/eventmanager.h"
#include "../../include/scenes/scene.h"
#include "../../include/scenes/debugscene.h"
#include "../../include/entities/cat.h"
#include "../../include/entities/button.h"
#include "../../include/util/camera.h"
#include "../../include/entities/cat_state.h"

/**
 * Constructor for the debug testing scene.
 */
void init_debug_scene(void) {
    if (!init_scene(gameData.scene)) {
        gameData.scene = NULL;
        return;
    }
    // Load assets for the debug scene.
    if (!push_asset_chunk(gameData.renderer, &gameData.assets,
                "./res/debug.manifest")) {
        free_scene(gameData.scene);
        gameData.scene = NULL;
        return;
    }
    // Init state.
    gameData.scene->state = (void*) malloc(sizeof(CatState));
    CatState* state = (CatState*) gameData.scene->state;
    // Set cat box bounds.
    state->bounds = transform_rect((SDL_Rect) { 0 }, 0.0f, -0.1f, 1.6f, 1.6f);
    // Time.
    state->remaining_time = 10 * 1000;  // 60 Seconds..
    state->score = 0;
    state->last_time = SDL_GetTicks();
    // Populate scene with entities.
    for (int i = 0; i < 50; i++) {
        float x = ((float) (rand() % 2) + ((float) rand() / RAND_MAX)) - 1.0f;
        float y = ((float) (rand() % 2) + ((float) rand() / RAND_MAX)) - 1.0f;
        INFO_LOG("%f %f\n", x, y);
        insert_entity(gameData.scene->entities.root, &init_cat,
                transform_rect(state->bounds, x, y, 0.1f, 0.1f));
    }
    insert_entity(gameData.scene->entities.root, &init_cat_state,
            transform_rect((SDL_Rect) { 0 }, 0.9f, 0.85f, 0.2f, 0.1f));
    gameData.scene->bg = get_asset_by_ref("debug-bg.png", 0)->pointer.texture;
    gameData.scene->cursor = get_asset_by_ref("cursor.png", 1)->pointer.texture;
    gameData.scene->event_handler = &default_handler;
    gameData.scene->type = Debug;
}

