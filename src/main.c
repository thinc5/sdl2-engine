#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/game.h"
#include "../include/timer.h"
#include "../include/assetmanager.h"
#include "../include/eventmanager.h"
#include "../include/renderer.h"
#include "../include/renderertemplates.h"

/**
 *  Initialize SDL components.
 */
 bool initModules(void) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Unable to initialize SDL_image\n");
        return false;
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "Unable to initialize SDL_ttf\n");
        return false;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        fprintf(stderr, "Unable to initialize SDL_mixer\n");
        return false;    
    }
    return true;
 }

/**
 * Quit SDL components.
 */
 void quitModules(void) {
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
 }

/**
 * Enassety point for Engine.
 */
int main(int argc, char* argv[]) {
    // Start all major game components.
    if (!initModules()) {
        return 1;
    }

    GameData gameData;
    if (!initGame(&gameData)) {
        fprintf(stderr, "Unable to initilize SDL.\n");
        return 2;
    }
    if (!loadAssets(gameData.renderer, gameData.assets, "./res/scene1.manifest")) {
        fprintf(stderr, "Unable to initilize SDL.\n");
        SDL_Quit();
        return 3;
    }
    
    int pickedTex = 0;

    // Dummy sdl rect
    SDL_Rect test = {
        .x = 50,
        .y = 50,
        .w = 50,
        .h = 50
    };
    // Main game loop
    startTimer(&gameData.fps->timer);
    while (gameData.status) {
        while (SDL_PollEvent(&gameData.event)) {
            // If person wants to exit i.e. alt+f4, clicking x, or for now esc
            if (gameData.event.type == SDL_QUIT) {
                // Clean up memory here and break main game loop
                printf("Caught SDL_QUIT, exiting now...\n");
                gameData.status = false;
                break;
            }
            scene1Manager(&gameData, &pickedTex);
        }
        // Draw
        SDL_RenderClear(gameData.renderer);
        renderBackground(gameData.renderer, getAssetByReference("cat1.jpg", gameData.assets)->pointer.texture);
        renderTexture(gameData.renderer, getAssetByReference("cat3.jpg", gameData.assets)->pointer.texture, &test);
        renderDebugMessage(gameData.renderer, getAssetByReference("ssp-regular.otf", gameData.assets)->pointer.font,
                getAssetByReference("ssp-regular.otf", gameData.assets)->reference);
        // renderFPS(gameData.renderer, gameData.assets->registry[7].pointer.font, gameData.fps->currentFPS);
        SDL_RenderPresent(gameData.renderer);
        updateTimer(gameData.fps);
    }

    freeGame(&gameData);
    quitModules();
    printf("Quitting now!\n");
    return 0;
}
