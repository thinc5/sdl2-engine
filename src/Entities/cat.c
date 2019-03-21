#include <stdio.h>

#include "../../include/entity.h"
#include "../../include/component.h"
#include "../../include/Entities/cat.h"

#include "../../include/Components/move.h"

/**
 * Behaviour of cat when clicked.
 */
void catRightClicked(void* e) {
    Entity* cat = (Entity*) e;
    unsigned int fattenBy = 10;
    cat->position.w += fattenBy;
    cat->position.h += fattenBy;
    cat->position.x -= fattenBy / 2;
    cat->position.y -= fattenBy / 2;
}

void catDraged(void *e, int x, int y) {
    Entity* cat = (Entity*) e;
    unsigned int fattenBy = 10;
    cat->position.w += fattenBy;
    cat->position.h += fattenBy;
    cat->position.x -= fattenBy / 2;
    cat->position.y -= fattenBy / 2;  
}

/**
 * Initilizes the cat entity and its components.
 */
Entity initCat(AssetRegistry* reg) {
    Entity cat;
    // Load cat assets make more flexable and specific later.
    if (!initEntity(&cat, reg, "cat4.jpg", "meow1.ogg")) {
        fprintf(stderr, "Could not initilize cat entity.\n");
        return (Entity) {};
    }
    // Cat specific specifiations
    // Starting position
    cat.position.x = 50;
    cat.position.y = 50;
    // Width and height
    cat.position.w = 20;
    cat.position.h = 20;
    // Load cat components.
    cat.components[Moved].call = &move;
    cat.components[RightClicked].call = &catRightClicked;
    cat.components[Draged].call = &catDraged;
    return cat;
}