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
    // Load assets for the main menu.
    if (!push_asset_chunk(gameData.renderer, &gameData.assets,
                "./res/debug.manifest")) {
        free_scene(gameData.scene);
        gameData.scene = NULL;
        return;
    }
    // Populate scene with entities.
    for (int i = 0; i < 50; i++) {
        float x = ((float) (rand() % 2) + ((float) rand() / RAND_MAX));
        float y = ((float) (rand() % 2) + ((float) rand() / RAND_MAX));
        //INFO_LOG("%f %f\n", x, y);
        add_entity(&gameData.scene->entities, &init_cat, transform_rect(0.1f, 0.1f, x, y));
    }
    gameData.scene->bg = get_asset_by_ref("cat3.jpg", 0)->pointer.texture;
    gameData.scene->cursor = get_asset_by_ref("cursor.png", 1)->pointer.texture;
    gameData.scene->event_handler = &default_handler;
    gameData.scene->type = Debug;
    // Init state.
    gameData.scene->state = (void*) malloc(sizeof(CatState));
    CatState* state = (CatState*) gameData.scene->state;
    // 
    state->remaining_time = 10 * 1000;  // 60 Seconds..
    state->score = 0;
    state->last_time = SDL_GetTicks();
    add_entity(&gameData.scene->entities, &init_cat_state,
            transform_rect(0.2f, 0.2f, 0.1f, 0.1f));
}

