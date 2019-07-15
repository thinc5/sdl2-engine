#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/util/camera.h"
#include "../../include/entities/entity.h"
#include "../../include/components/move.h"

/**
 * Move an entity a set distance in a provided direction.
 */
void move(void* e, Direction d, int pixels, SDL_Rect bounds) {
    if (bounds.w == 0) {
        SDL_GL_GetDrawableSize(gameData.window, &bounds.w, &bounds.h);
    }
    // INFO_LOG("Window = %d %d\n", screen_pos.w, screen_pos.h);
    Entity* entity = (Entity*) e;
    SDL_Rect new_pos = entity->position;
    switch (d) {
        case UP:
            new_pos.y -= pixels;
            if (is_inside(new_pos, bounds)) {
                entity->position = new_pos;
            } else {
                entity->position.y = bounds.y;
            }
            break;
        case DOWN:
            new_pos.y += pixels;
            if (is_inside(new_pos, bounds)) {
                entity->position = new_pos;
            } else {
                entity->position.y = bounds.h - entity->position.h;
            }
            break;
        case LEFT:
            new_pos.x -= pixels;
            if (is_inside(new_pos, bounds)) {
                entity->position = new_pos;
            } else {
                entity->position.x = bounds.x;
            }
            break;
        case RIGHT:
            new_pos.x += pixels;
            if (is_inside(new_pos, bounds)) {
                entity->position = new_pos;
            } else {
                entity->position.x = bounds.w - entity->position.w;
            }
            break;
        default:
            break;
    }
}

