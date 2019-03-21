#ifndef COMPONENT_H
#define COMPONENT_H

/**
 * All types of components are listed here.
 */
typedef enum ComponentType {
    Render,
    LeftClicked,
    RightClicked,
    Draged,
    Moved,
    Deleted,
    COMPONENT_TOTAL,
} ComponentType;

/**
 * Definition of a component.
 */
typedef struct Component {
    void (*call)(); 
} Component; 

#endif