#include <math.h>
#include <stdio.h>

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

/**
 * Constructor for the debug testing scene.
 */
void init_debug_scene(void) {
    if (!init_scene(gameData.scene)) {
        gameData.scene = NULL;
        return;
    }

    // Load assets for the main menu.
    if (!push_asset_chunk(gameData.renderer, &gameData.scene->assets,
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
        add_entity(&gameData.scene->entities, &gameData.scene->assets, &init_cat,
	            transform_rect(gameData.renderer, 0.1, 0.1, x, y));
    }
    gameData.scene->bg = get_asset_by_ref("cat3.jpg", &gameData.scene->assets,0)->pointer.texture;
    gameData.scene->cursor = get_asset_by_ref("cursor.png", &gameData.scene->assets,0)->pointer.texture;
    gameData.scene->event_handler = &default_handler;
    gameData.scene->type = Debug;
}
