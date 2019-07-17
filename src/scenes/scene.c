#include <stdlib.h>
#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/util/camera.h"
#include "../../include/managers/assetstack.h"
#include "../../include/managers/quadtree.h"
#include "../../include/scenes/scene.h"

#include "../../include/rendering/renderertemplates.h"

/**
 * Initialize the scene components.
 */
bool init_scene(Scene* scene) {
    init_quad_tree(&scene->entities, (SDL_Rect) { 0 });
    // No background or cursor by default.
    scene->bg = NULL;
    scene->cursor = NULL;
    scene->state = NULL;
    return true;
}

/**
 * Free a scene.
 */
void free_scene(Scene* scene) {
    // Free all remaining entities.
    free_quad_tree(&scene->entities);
    INFO_LOG("Freeing entities.\n");
    // Remove event handler pointer.
    scene->event_handler = NULL;
    // Remove references to bg and cursor.
    scene->bg = NULL;
    scene->cursor = NULL;
    // Free the scene state.
    INFO_LOG("Freeing scene state.\n");
    if (scene->state != NULL) {
        free(scene->state);
        scene->state = NULL;
    }
    INFO_LOG("Freeing scene asset chunk.\n");
    // Free the top chunk of assets.
    pop_asset_chunk(&gameData.assets);
}

/**
 * Switch scenes.
 */
void change_scene(void (*next)(void)) {
    // Draw loading notification :)
    SDL_Rect pos = transform_rect((SDL_Rect) { 0 }, 0.0f, 0.0f, 0.4f, 0.2f);
    render_texture(get_asset_by_ref("loading.png", 0)->pointer.texture, &pos);
    SDL_RenderPresent(gameData.renderer);
    // Check if we need to free the scene.
    if (gameData.currentScene->type != MainMenu) {
        free_scene(gameData.scene);
        free(gameData.scene);
        gameData.scene = NULL;
        // Dont do this, we keep the scene allocated; gameData.scene = NULL;
    }
    // Check if we are returning to main menu (already loaded);
    if (next != NULL) {
        gameData.scene = (Scene*) malloc(sizeof(Scene));
        next();
        // Change the pointer to the new scene.
        gameData.currentScene = gameData.scene;
    } else {
        gameData.currentScene = gameData.menu;
    }
}

