#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/debug.h"
#include "../include/util/framerate.h"
#include "../include/managers/assetstack.h"
#include "../include/managers/eventmanager.h"
#include "../include/rendering/renderer.h"
#include "../include/rendering/renderertemplates.h"
#include "../include/entities/cat.h"
#include "../include/entities/button.h"
#include "../include/game.h"
#include "../include/scenes/scene.h"
#include "../include/scenes/debugscene.h"


/**
 *  Initialize SDL components.
 */
static bool init_modules(void) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        ERROR_LOG("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        ERROR_LOG("Unable to initialize SDL_image\n");
        return false;
    }
    if (TTF_Init() != 0) {
        ERROR_LOG("Unable to initialize SDL_ttf\n");
        return false;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        ERROR_LOG("Unable to initialize SDL_mixer\n");
        return false;
    }
    return true;
 }

/**
 * Quit SDL components.
 */
static void quit_modules(void) {
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
 }

#ifdef DEBUG
/**
 * Debug function to show location of mouse.
 */
static void mouse_dbg(SDL_Renderer* renderer, TTF_Font* fnt) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    char mouse[40];
    sprintf(mouse, "MPOS: x %d y %d", x, y);
    render_debug_message(renderer, fnt, mouse);
}
#endif

/**
 * Entry point for the engine.
 */
int main(int argc, char** argv) {
    // Start all major game components.
    if (!init_modules()) {
        return 1;
    }
    
    // Load game components and state.
    GameData gameData;
    if (!init_game(&gameData)) {
        ERROR_LOG("Unable to initialize game modules.\n");
        return 1;
    }
    
    // Debug Assets
    SDL_Texture* bg = get_asset_by_ref("cat1.jpg",
            (&gameData.scene->assets), 0)->pointer.texture;

    #ifdef DEBUG
    TTF_Font* fnt = get_asset_by_ref("ssp-regular.otf",
            &gameData.scene->assets, 0)->pointer.font;
    #endif
    
    // Scene in focus.
    Scene* currentScene = gameData.menu;

    // Main game loop.
    while (gameData.status) {
        // ---------------- Handle user events.
        while (SDL_PollEvent(&gameData.event)) {
            if (gameData.event.type == SDL_QUIT) {
                gameData.status = false;
                break;
            }
            // Testing unloading/reloading scenes.
            if (gameData.event.key.keysym.sym == SDLK_F1) {
                // Load next level.
                free_scene(gameData.scene);
                init_debug_scene(gameData.renderer, gameData.scene);
            }
            currentScene->event_handler(&gameData, currentScene);
        }

        //----------------- Update state.
        for (int i = 0; i < currentScene->entities.current; i++) {
            if (has_component(&currentScene->entities.entities[i],
                    OnTick)) {
                currentScene->entities.entities[i].components[OnTick]
                        .call(&currentScene->entities.entities[i]);
            }
        }

        // Remove all entities marked for deletion.
        clean_entities(&currentScene->entities);

        // --------------- Render state.
        SDL_RenderClear(gameData.renderer);
        
	    render_background(gameData.renderer, bg);
        render_entities(&gameData, currentScene);
        
	    #ifdef DEBUG
	    mouse_dbg(gameData.renderer, fnt);
        #endif

	    SDL_RenderPresent(gameData.renderer);

        // --------------- Wait if we have finished too soon.
        cap_fps(&gameData.fps);
    }

    // Game over, free everything.
    free_game(&gameData);
    quit_modules();
    return 0;
}

