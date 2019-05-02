#include "../../include/managers/assetmanager.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/scenes/scene.h"

/**
 * Initialize the scene components.
 */
bool initScene(Scene* scene) {
    if (!initAssetManager(&scene->assets)) {
        return false;
    }
    if (!initEntityManager(&scene->entities)) {
        freeAssets(&scene->assets);
        return false;
    }
    return true;
}

/**
 * Free a scene.
 */
void freeScene(Scene* scene) {
    freeAssets(&scene->assets);
    freeEntities(&scene->entities);
}