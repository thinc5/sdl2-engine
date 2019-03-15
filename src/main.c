#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/game.h"
#include "../include/util.h"
#include "../include/timer.h"
#include "../include/assetmanager.h"
#include "../include/eventmanager.h"
#include "../include/renderer.h"
#include "../include/renderertemplates.h"

/**
 * Enassety point for Engine.
 */
int main(int argc, char* argv[]) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) == 0) {
        printf("Unable to initialize SDL_image\n");
        return 1;
    }
    if (TTF_Init() != 0) {
        printf("Unable to initialize SDL_ttf");
        return 1;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        return 1;    
    }


    // Start all major game components.
    GameData gameData;
    initGame(&gameData);
    if (!loadAssets(gameData.renderer, gameData.assets, "./res/scene1_textures.conf")) {
        SDL_Quit();
        return 2;
    }

    printf("Loaded %d out of %d textures!\n", gameData.assets->currentSize,
            gameData.assets->totalSize);
    
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
        renderBackground(gameData.renderer, gameData.assets->registry[pickedTex].pointer.texture);
        // renderTexture(gameData.renderer, gameData.assets->register[3].pointer.texture, &test);
        // renderDebugMessage(gameData.renderer, gameData.assets->register[7].pointer.font, gameData.assets->register[pickedTex].reference);
        // renderFPS(gameData.renderer, gameData.assets->register[7].pointer.font, gameData.fps->currentFPS);
        SDL_RenderPresent(gameData.renderer);
        updateTimer(gameData.fps);
    }

    printf("Freeing game data..\n");
    freeGame(&gameData);
    printf("Quitting now!\n");
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
