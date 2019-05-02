#include "../../include/managers/assetmanager.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/managers/eventmanager.h"

#include "../../include/scenes/scene.h"
#include "../../include/scenes/mainmenu.h"

#include "../../include/entities/cat.h"
#include "../../include/entities/button.h"

/**
 * Constructor for the debug testing scene.
 */
Scene initDebugScene(SDL_Renderer* renderer) {
    Scene scene;
    if (!initScene(&scene)) {
        return (Scene) { 0 };
    }
    // Load assets for the main menu.
    if (!loadAssets(renderer, &scene.assets, "./res/debug.manifest")) {
        freeScene(&scene);
        return (Scene) { 0 };
    }
    // Populate scene with entities.
    for (int i = 0; i < 50; i++) {
        addEntity(&scene.entities, &scene.assets, &initCat);
    }
    addEntity(&scene.entities, &scene.assets, &initButton);
    scene.eventHandler = &default_handler;
    scene.type = MainMenu;
    return scene;
}

