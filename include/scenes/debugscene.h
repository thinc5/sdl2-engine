#ifndef DEBUGSCENE_H
#define DEBUGSCENE_H

#include <stdbool.h>

#include "../scenes/scene.h"

bool init_debug_scene(SDL_Renderer* renderer, SDL_Window* window,
        Scene* scene);

#endif
