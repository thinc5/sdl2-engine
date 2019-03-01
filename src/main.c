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
    if (!update_workingdir(argv[0])) {
        return 2;
    }
    // Start all major game components.
    GameData gameData = initialize_game();
    
    if (!loadTextures(gameData.renderer, &gameData.tr, "scene1.config")) {
        SDL_Quit();
        return false;
    }
    int pickedTex = 0;
    // Main game loop
    bool game = true;
    while (game) {
        setStartTime(&gameData.fps);
        while (SDL_PollEvent(&gameData.event)) {
            // If person wants to exit i.e. alt+f4 or clicking x
            if (gameData.event.type == SDL_QUIT) {
                // Clean up memory here and break main game loop
                printf("Caught SDL_QUIT, exiting now...\n");
                game = false;
                continue;
            }
            // Picked texture
            if (pickedTex + 1 < gameData.tr.currentSize) {
                pickedTex++;
            } else {
                pickedTex = 0;
            }
            // Draw
            SDL_RenderClear(gameData.renderer);
            if (SDL_RenderCopy(gameData.renderer, (&gameData.tr)->registry[pickedTex].texture, NULL, NULL) == -1) {
                printf("Failed to render texture..\n");
            }
            SDL_RenderPresent(gameData.renderer);
        showFPS(&gameData.fps);
        setEndTime(&gameData.fps);
        }
    }
    freeTextures(&gameData.tr);
    SDL_DestroyRenderer(gameData.renderer);
    SDL_DestroyWindow(gameData.window);
    SDL_Quit();
    return 0;
}
