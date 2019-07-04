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
    return true;
}

/**
 * Free a scene.
 */
void free_scene(Scene* scene) {
    // Free all remaining entities.
    free_entities(&scene->entities);
    // Free the top chunk of assets.
    pop_asset_chunk(&gameData.assets);
}

/**
 * Switch scenes.
 */
void change_scene(void (*next)(void)) {
    // Draw loading notification :)
    SDL_Rect pos = transform_rect(0.4f, 0.2f, 1.0f, 1.0f);
    render_texture(get_asset_by_ref("loading.png", 0)->pointer.texture, &pos);
    SDL_RenderPresent(gameData.renderer);
    // Check if we need to free the scene.
    if (gameData.currentScene->type != MainMenu) {
        free(gameData.scene);
        gameData.scene = NULL;
    }
    // Allocate space for the new scene.
    gameData.scene = (Scene*) malloc(sizeof(Scene));
    // Load the new scene.
    next();
    // Change the pointer to the new scene.
    gameData.currentScene = gameData.scene;
}

