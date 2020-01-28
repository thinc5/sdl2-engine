#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/managers/assetstack.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/managers/eventmanager.h"
#include "../../include/scenes/scene.h"
#include "../../include/scenes/quadtreescene.h"
#include "../../include/util/camera.h"
#include "../../include/games/catgame/cat.h"
#include "../../include/games/catgame/catbutton.h"

/**
 * Constructor for the quadtree testing scene.
 */
void init_quadtree_scene(void) {
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
    gameData.scene->event_handler = &default_handler;
    gameData.scene->type = Debug;
}

