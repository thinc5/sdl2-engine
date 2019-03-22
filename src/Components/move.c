#include "../../include/entity.h"
#include "../../include/Components/move.h"

/**
 * Move an entity a set distance in a provided direction.
 */
void move(void* e, Direction d) {
    Entity* entity = (Entity*) e;
    switch (d) {
        case UP:
            entity->position.y -= 1;
            break;
        case DOWN:
            entity->position.y += 1;
            break;
        case LEFT:
            entity->position.x -= 1;
            break;
        case RIGHT:
            entity->position.x += 1;
            break;
        default:
            break;
    }
}

