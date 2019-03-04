#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "../include/game.h"
#include "../include/util.h"
#include "../include/frameratemanager.h"
#include "../include/texturemanager.h"

/**
 * Entry point for Engine.
 */
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    // if (!update_workingdir(argv[0])) {
    //     return 2;
    // }
    // Start all major game components.
    GameData gameData = initGame();
    if (!loadTextures(gameData.renderer, gameData.tr, "./res/scene1.txt")) {
        SDL_Quit();
        return false;
    }
    printf("Loaded %d out of %d textures!\n", gameData.tr->currentSize, gameData.tr->totalSize);
    int pickedTex = 0;
    // Main game loop
    bool game = true;
    while (game) {
        startTimer(gameData.fps);
        while (SDL_PollEvent(&gameData.event)) {
            printf("We have an event!!\n");
            // If person wants to exit i.e. alt+f4 or clicking x
            if (gameData.event.type == SDL_QUIT) {
                // Clean up memory here and break main game loop
                printf("Caught SDL_QUIT, exiting now...\n");
                game = false;
                break;
            }
        }
        printf("Test!\n");
        // Draw
        SDL_RenderClear(gameData.renderer);
        printf("Test!\n");
        if (SDL_RenderCopy(gameData.renderer, gameData.tr->registry[pickedTex].texture, NULL, NULL) == -1) {
            printf("Failed to render texture..\n");
        }
        printf("Test!\n");
        SDL_RenderPresent(gameData.renderer);
        showFPS(gameData.fps);
        updateTimer(gameData.fps);
    }
    printf("Quitting now!\n");
    freeGame(&gameData);
    SDL_Quit();
    return 0;
}
