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

#ifdef DEBUG
/**
 * Debug function to show location of mouse.
 */
static void mouse_dbg(TTF_Font* fnt) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    char mouse[40];
    sprintf(mouse, "MPOS: x %d y %d x %d y %d", x, y);
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
    //INFO_LOG("Polling Events\n");
    while (SDL_PollEvent(&gameData.event)) {
        if (gameData.event.type == SDL_QUIT) {
            gameData.status = false;
            break;
        }
        gameData.currentScene->event_handler();
    }
    //INFO_LOG("Events Polled\n");
}

/**
  * Update game state.
  */
static void update_state(void) {
    //INFO_LOG("Updating State\n");
    for (int i = 0; i < gameData.currentScene->entities.current; i++) {
        if (has_component(&gameData.currentScene->entities.entities[i],
                OnTick)) {
            gameData.currentScene->entities.entities[i].components[OnTick]
                    .call(&gameData.currentScene->entities.entities[i]);
        }
    }
    // Remove all entities marked for deletion.
    clean_entities(&gameData.currentScene->entities);
    //INFO_LOG("State Updated\n");
}

/**
 * Render game state.
 */
static void render_state(void) {
    //INFO_LOG("Rendering\n");
    SDL_RenderClear(gameData.renderer);
	render_background(gameData.currentScene);
    render_entities(gameData.currentScene);
    render_cursor(gameData.currentScene);
    #ifdef DEBUG
    mouse_dbg(get_asset_by_ref("ssp-regular.otf", 0)->pointer.font);
    #endif
    SDL_RenderPresent(gameData.renderer);
    //INFO_LOG("Rendered\n");
}

/**
 * Entry point for the engine.
 */
int main(int argc, char** argv) {
    // Start all SDL components and load the game.
    if (!init_modules() || !init_game(&gameData)) {
        ERROR_LOG("Unable to initialize game modules.\n");
        return 1;
    }
    // Main game loop.
    INFO_LOG("Game Loop\n");
    while (gameData.status) {
        // ---------------- Handle user events.
        handle_events();
        //----------------- Update state.
        update_state();
        // --------------- Render state.
        render_state();
        // --------------- Wait if we have finished too soon.
        cap_fps(&gameData.fps);
    }
    // Clean up.
    free_game(&gameData);
    quit_modules();
    return 0;
}

