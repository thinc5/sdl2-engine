#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include "../include/config.h"
#include "../include/debug.h"
#include "../include/util/os.h"
#include "../include/util/framerate.h"
#include "../include/managers/asset.h"
#include "../include/managers/assetstack.h"
#include "../include/managers/eventmanager.h"
#include "../include/rendering/renderer.h"
#include "../include/rendering/renderertemplates.h"
#include "../include/game.h"
#include "../include/scenes/scene.h"
#include "../include/games/catgame/catbutton.h"

#ifdef DEBUG
// Font to be used to render debug messages.
static RegisteredAsset* fnt;

/**
 * Debug function to show location of mouse.
 */
static void mouse_dbg(TTF_Font* fnt) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    char mouse[40];
    sprintf(mouse, "MPOS: x %d y %d", x, y);
    render_debug_message(fnt, mouse);
}
#endif

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

/**
 * Handle the user events.
 */
static void handle_events(void) {
    while (SDL_PollEvent(&gameData.event)) {
        if (gameData.event.type == SDL_QUIT) {
            gameData.status = CLOSING;
            break;
        }
        gameData.currentScene->event_handler();
    }
}

/**
  * Update game state.
  */
static void update_state(void) {
    // Do not process any entities whilst we are loading scenes.
    if (gameData.status == LOADING) {
        return;
    }
    for (int i = 0; i < gameData.currentScene->entities.current; i++) {
        if (has_component(&gameData.currentScene->entities.entities[i],
                OnTick)) {
            gameData.currentScene->entities.entities[i].components[OnTick]
                    .call(&gameData.currentScene->entities.entities[i]);
        }
    }
    // Remove all entities marked for deletion.
    clean_entities(&gameData.currentScene->entities);
}

/**
 * Render game state.
 */
static void render_state(void) {
    SDL_SetRenderDrawColor(gameData.renderer, 255, 0, 0, 255);
    SDL_RenderClear(gameData.renderer);
	render_background(gameData.currentScene);
    render_entities(gameData.currentScene);
    render_cursor(gameData.currentScene);
    #ifdef DEBUG
    mouse_dbg(fnt->pointer.font);
    #endif
    SDL_RenderPresent(gameData.renderer);
}

/**
 * Entry point for the engine.
 */
int main(int argc, char** argv) {
    // Change working directory to the directory of the executable
    // (allows exe to be used from any path).
    set_dir();
    INFO_LOG("Launching: \"%s\"\n", WINDOW_TITLE);
    // Start all SDL components and load the game.
    if (!init_modules() || !init_game(&gameData)) {
        ERROR_LOG("Unable to initialize game modules.\n");
        return 1;
    }

    // Seed rand() to make it seem actually random.
    srand(time(NULL));
    
    #ifdef DEBUG
    fnt = get_asset_by_ref("ssp-regular.otf", 0);
    #endif

    // Main game loop.
    INFO_LOG("Initialized at %s\n", gameData.currentScene->title);
    while (gameData.status != CLOSING) {
        switch (gameData.status) {
            case RUNNING:
                // Handle user events.
                handle_events();
                // Update state.
                update_state();
                // Render state.
                render_state();
                // Wait if we have finished too soon (capping fps).
                cap_fps(&gameData.fps);
                break;
            case LOADING:
                // Display loading notification?
                break;
            default:
                break;
        }
    }
    
    // Clean up.
    free_game(&gameData);
    quit_modules();
    INFO_LOG("\"%s\" terminated\n", WINDOW_TITLE);
    return 0;
}
