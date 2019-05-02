#include "../../include/managers/assetmanager.h"
#include "../../include/managers/entitymanager.h"
#include "../../include/managers/eventmanager.h"

#include "../../include/scenes/scene.h"
#include "../../include/scenes/mainmenu.h"

#include "../../include/entities/cat.h"
#include "../../include/entities/button.h"

Scene initMainMenu(SDL_Renderer* renderer) {
    Scene scene;
    if (!initScene(&scene)) {
        return (Scene) {};
    }
    // Load assets for the main menu.
    if (!loadAssets(renderer, &scene.assets, "./res/mainmenu.manifest")) {
        freeScene(&scene);
        return (Scene) {};
    }
    // Populate scene with entities.
    addEntity(&scene.entities, &scene.assets, &initButton);
    scene.eventHandler = &default_handler;
    scene.type = MainMenu;
    return scene;
}

