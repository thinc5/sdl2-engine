#include <stdbool.h>

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
bool init_debug_scene(SDL_Renderer* renderer, SDL_Window* window,
        Scene* scene) {
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
        add_entity(&scene->entities, &scene->assets, &init_cat,
	        transform_rect(window, 0.2f, 0.1f, 0.5f, 1.5f));
    }
    
    scene->event_handler = &default_handler;
    scene->type = MainMenu;
    
    return scene;
}

