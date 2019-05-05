#include "../../include/debug.h"
#include "../../include/managers/assetstack.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/managers/eventmanager.h"
#include "../../include/scenes/scene.h"
#include "../../include/scenes/mainmenu.h"
#include "../../include/entities/cat.h"
#include "../../include/entities/button.h"

Scene init_main_menu(SDL_Renderer* renderer) {
    Scene scene;
    if (!init_scene(&scene)) {
	INFO_LOG("Unable to init scene.\n");
        return (Scene) { 0 };
    }
    // Load assets for the main menu.
    if (!push_asset_chunk(renderer, &scene.assets, "./res/mainmenu.manifest")) {
        free_scene(&scene);
	INFO_LOG("Failed to load the scene.\n");
        return (Scene) { 0 };
    }
    // Populate scene with entities.
    add_entity(&scene.entities, &scene.assets, &init_button);
    scene.event_handler = &default_handler;
    scene.type = MainMenu;
    INFO_LOG("Main menu scene created.\n");
    return scene;
}

