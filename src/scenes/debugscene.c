#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "../../include/debug.h"
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
bool init_debug_scene(SDL_Renderer* renderer, Scene* scene) {
    if (!init_scene(scene)) {
        return false;
    }

    // Load assets for the main menu.
    if (!push_asset_chunk(renderer, &scene->assets,
            "./res/debug.manifest")) {
        free_scene(scene);
        return false;
    }

    // Populate scene with entities.
    for (int i = 0; i < 50; i++) {
        float x = ((float) (rand() % 2) + ((float) rand() / RAND_MAX));
        float y = ((float) (rand() % 2) + ((float) rand() / RAND_MAX));
        INFO_LOG("%f %f\n", x, y);
        add_entity(&scene->entities, &scene->assets, &init_cat,
	            transform_rect(renderer, 0.1, 0.1, x, y));
    }
    scene->bg = get_asset_by_ref("cat3.jpg", &scene->assets,0)->pointer.texture;
    scene->cursor = get_asset_by_ref("cursor.png", &scene->assets,0)->pointer.texture;
    scene->event_handler = &default_handler;
    scene->type = MainMenu;
    
    return scene;
}
