#include "../../include/debug.h"
#include "../../include/game.h"
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
void init_main_menu(void) {
    if (!init_scene(gameData.menu)) {
        ERROR_LOG("Unable to init menu.\n");
        gameData.menu = NULL;
        return;
    }
    // Load assets for the main menu.
    if (!push_asset_chunk(gameData.renderer, &gameData.assets,
                "./res/mainmenu.manifest")) {
        free_scene(gameData.scene);
	    ERROR_LOG("Failed to load the scene.\n");
        gameData.menu = NULL;
        return;
    }
    add_entity(&gameData.menu->entities, &init_button, transform_rect(0.4f, 0.2f, 1.0f, 1.4f));
    add_entity(&gameData.menu->entities, &init_play_button, transform_rect(0.4f, 0.2f, 1.0f, 0.6f));
    // Add event handler and window type.
    gameData.menu->event_handler = &default_handler;
    gameData.menu->bg = get_asset_by_ref("cat1.jpg", 0)->pointer.texture;
    gameData.menu->type = MainMenu;
}

