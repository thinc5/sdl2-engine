#include "../../include/managers/assetstack.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/managers/eventmanager.h"
#include "../../include/scenes/scene.h"
#include "../../include/scenes/debugscene.h"
#include "../../include/entities/cat.h"
#include "../../include/entities/button.h"

/**
 * Constructor for the debug testing scene.
 */
Scene init_debug_scene(SDL_Renderer* renderer) {
    Scene scene;
    if (!init_scene(&scene)) {
        return (Scene) { 0 };
    }
    // Load assets for the main menu.
    if (!push_asset_chunk(renderer, &scene.assets, "./res/debug.manifest")) {
        free_scene(&scene);
        return (Scene) { 0 };
    }
    // Populate scene with entities.
    for (int i = 0; i < 50; i++) {
        add_entity(&scene.entities, &scene.assets, &init_cat);
    }
    add_entity(&scene.entities, &scene.assets, &init_button);
    scene.event_handler = &default_handler;
    scene.type = MainMenu;
    return scene;
}

