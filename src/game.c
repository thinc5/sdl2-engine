#include <SDL2/SDL.h>

#include "../include/config.h"
#include "../include/game.h"

GameData initialize_game() {
    // Create the window
    GameData gameData;
    gameData.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE),
    // Create the renderer
    gameData.renderer = SDL_CreateRenderer(gameData.window, -1, SDL_RENDERER_ACCELERATED);
    // Set default background colour
    SDL_SetRenderDrawColor(gameData.renderer, 255, 0, 0, 255);
    // Custom framerate manager
    gameData.fps.startTime = 0;
    gameData.fps.endTime = 0;
    gameData.fps.delta = 0;
    gameData.fps.fpsCap = FRAME_CAP;
    gameData.fps.timePerFrame = (1000 / FRAME_CAP); // 1000 / prefered fps
    // Custom texture registry
    gameData.tr.currentSize = 0;
    gameData.tr.totalSize = 0;
    return gameData;
}
