#include "../../include/entity.h"
#include "../../include/Components/move.h"

/**
 * Move an entity a set distance in a provided direction.
 */
void move(void* e, Direction d) {
    Entity* entity = (Entity*) e;
    switch (d) {
        case UP:
            entity->position.y -= 50;
            break;
        case DOWN:
            entity->position.y += 50;
            break;
        case LEFT:
            entity->position.x -= 50;
            break;
        case RIGHT:
            entity->position.x += 50;
            break;
        default:
            break;
    }
}

