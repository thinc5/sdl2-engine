#include <stdio.h>

#include "../../include/entity.h"
#include "../../include/component.h"
#include "../../include/Entities/cat.h"

#include "../../include/Components/move.h"

/**
 * Behaviour of cat when clicked.
 */
void catClicked(void* e) {
    printf("Cat was clicked!\n");
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
    // Cat specific specifiations
    // Starting position
    cat.position.x = 0;
    cat.position.y = 0;
    // Width and height
    cat.position.w = 20;
    cat.position.h = 20;
    // Load cat assets make more flexable and specific later.
    if (!initEntity(&cat, reg, "cat4.jpg", "meow1.ogg")) {
        fprintf(stderr, "Could not initilize cat entity.\n");
        return (Entity) {};
    }
    // Load cat components.
    cat.components[Moved].call = &move;
    cat.components[Clicked].call = &catClicked;
    return cat;
}