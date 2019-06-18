#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/managers/assetstack.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/scenes/scene.h"

#include "../../include/rendering/renderertemplates.h"

/**
 * Initialize the scene components.
 */
bool init_scene(Scene* scene) {
    if (!init_asset_stack(&scene->assets)) {
	ERROR_LOG("Unable to create asset stack.\n");
        return false;
    }
    if (!init_entity_manager(&scene->entities)) {
	ERROR_LOG("Unable to create entity manager.\n");
        free_asset_stack(&scene->assets);
        return false;
    }
    return true;
}

/**
 * Free a scene.
 */
void free_scene(Scene* scene) {
    // Free all remaining entities.
    free_entities(&scene->entities);
    // Free the top chunk of assets.
    pop_asset_chunk(&scene->assets);
}

/**
 * Load a new scene and replace current scene.
 */
void replace_scene(Scene* current, Scene* next) {
    // Free scene and load next.
    free_scene(current);
    free(current);
    current = next;
}
