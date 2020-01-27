#include <stdlib.h>
#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/util/camera.h"
#include "../../include/managers/assetstack.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/scenes/scene.h"

#include "../../include/rendering/renderertemplates.h"

/**
 * Initialize the scene components.
 */
bool init_scene(Scene* scene) {
    if (!init_entity_manager(&scene->entities)) {
	    ERROR_LOG("Unable to create entity manager.\n");
        free_asset_stack(&gameData.assets);
        return false;
    }
    // No background or cursor by default.
    scene->bg = NULL;
    scene->cursor = NULL;

    // No scene state by default.
    scene->state = NULL;
    return true;
}

/**
 * Free a scene.
 */
void free_scene(Scene* scene) {
    if (scene == NULL) {
        DEBUG_LOG("Scene already freed.\n");
        return;
    }

    free_entities(&scene->entities);
    // Remove event handler pointer.
    scene->event_handler = NULL;
    // Remove references to bg and cursor.
    scene->bg = NULL;
    scene->cursor = NULL;
    // Free the scene state.
    free(scene->state);
    scene->state = NULL;
    // Free the top chunk of assets.
    pop_asset_chunk(&gameData.assets);
}

/**
 * Switch scenes.
 */
void change_scene(void (*next)(void)) {
    DEBUG_LOG("Changing scene.\n");
    gameData.status = LOADING;
    // Draw loading notification :)
    SDL_Rect pos = transform_rect(0.4f, 0.2f, 1.0f, 1.0f);
    render_texture(get_asset_by_ref("loading.png", 0)->pointer.texture, &pos);
    SDL_RenderPresent(gameData.renderer);
    
    // Check if we need to free the scene.
    if (gameData.currentScene->type != MainMenu) {
        DEBUG_LOG("Not main menu, freeing the scene.\n");
        free_scene(gameData.scene);
        free(gameData.scene);
        gameData.scene = NULL;
    }
    
    // Are we going to the main menu?
    if (next != NULL) {
        // Load the new scene.
        if (gameData.scene == NULL) {
            gameData.scene = (Scene*) malloc(sizeof(Scene));
        }
        next();
        // Change the pointer to the new scene.
        gameData.currentScene = gameData.scene;
        gameData.status = RUNNING;
        return;
    }
    // We are returning to the main menu, change the current scene to the main menu.
    gameData.scene = NULL;
    gameData.currentScene = gameData.menu;
    gameData.status = RUNNING;
}
