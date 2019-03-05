#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "../include/game.h"
#include "../include/util.h"
#include "../include/timer.h"
#include "../include/texturemanager.h"

/**
 * Entry point for Engine.
 */
int main(int argc, char* argv[]) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) == 0) {
        printf("Unable to initialize SDL_image\n");
    }
    // Start all major game components.
    GameData gameData;
    initGame(&gameData);
    if (!loadTextures(gameData.renderer, gameData.tr, "./bin/res/scene1.txt")) {
        SDL_Quit();
        return false;
    }
    printf("Loaded %d out of %d textures!\n", gameData.tr->currentSize, gameData.tr->totalSize);
    int pickedTex = 0;
    // Main game loop
    while (!gameData.renderer);
    bool game = true;
    while (game) {
        startTimer(&gameData.fps->timer);
        while (SDL_PollEvent(&gameData.event)) {
            // If person wants to exit i.e. alt+f4, clicking x, or for now esc
            if (gameData.event.type == SDL_QUIT) {
                // Clean up memory here and break main game loop
                printf("Caught SDL_QUIT, exiting now...\n");
                game = false;
                break;
            }
            if (gameData.event.type == SDL_KEYDOWN) {
                switch (gameData.event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        game = false;
                        break;
                    case SDLK_LEFT:
                        if (pickedTex - 1 < 0) {
                            pickedTex = gameData.tr->currentSize - 1;
                        } else {
                            pickedTex--;
                        }
                        break;
                    case SDLK_RIGHT:
                    if (pickedTex + 1 < gameData.tr->currentSize) {
                            pickedTex++;
                        } else {
                            pickedTex = 0;
                        }
                        break;
                    default:
                        break;
                }
                printf("Selected Texture: %s\n", "LOL");//gameData.tr->registry[pickedTex].reference);
            }
        }
        // Draw
        SDL_RenderClear(gameData.renderer);
        if (SDL_RenderCopy(gameData.renderer, gameData.tr->registry[pickedTex].texture, NULL, NULL) == -1) {
            printf("Failed to render texture..\n");
            game = false;
        }
        SDL_RenderPresent(gameData.renderer);
        //showFPS(gameData.fps);
        updateTimer(gameData.fps);
    }
    printf("Quitting now!\n");
    freeGame(&gameData);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
