#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/managers/assetstack.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/managers/eventmanager.h"
#include "../../include/scenes/scene.h"
#include "../../include/scenes/mainmenu.h"
#include "../../include/entities/cat.h"
#include "../../include/entities/button.h"
#include "../../include/util/camera.h"

/**
 * Constructor for the main menu.
 */
bool init_main_menu(SDL_Renderer* renderer, SDL_Window* window,
        Scene* scene) {
    if (!init_scene(scene)) {
        INFO_LOG("Unable to init menu.\n");
        return false;
    }
    
    // Load assets for the main menu.
    if (!push_asset_chunk(renderer, &scene->assets,
            "./res/mainmenu.manifest")) {
        free_scene(scene);
	INFO_LOG("Failed to load the scene.\n");
        return false;
    }
    
    // Add our buttons! 
    add_entity(&scene->entities, &scene->assets, &init_button,
            transform_rect(window, 0.4f, 0.2f, 1.0f, 0.5f));
    add_entity(&scene->entities, &scene->assets, &init_button,
            transform_rect(window, 0.4f, 0.2f, 1.0f, 1.0f)); 
    add_entity(&scene->entities, &scene->assets, &init_button,
            transform_rect(window, 0.4f, 0.2f, 1.0f, 1.5f));
    
    // Add event handler and window type.
    scene->event_handler = &default_handler;
    scene->type = MainMenu;
    
    INFO_LOG("Main menu scene created.\n");
    return true;
}

