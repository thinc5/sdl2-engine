#include <SDL.h>

/**
 * Entry point for Engine.
 */
int main(int argc, char* argv[])
{
    // Lmao look tony u dumb this is how you use these options
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    /* ... */

    SDL_Quit();

    return 0;
}
