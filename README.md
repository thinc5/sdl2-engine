# SDL2 based 2D Game Engine

## About
I've always been interested in video games and I figured it was time to attempt to write my own (engine).
I chose SDL2 as my starting point as it was written in C, is cross platform and has lots of documentation.
C was my first choice of language due to performance, flexibility and in all honesty, just to improve my skills with it and have fun in the process.

## Compilation

### Linux
- Install sdl2-dev, sdl2-image, sdl2-ttf and sdl2-mixer from your package manager.

### Windows
- Requires mingw32, gcc, make, sdl2(mingw32), sdl_image(mingw32), sdl_ttf(mingw32) and sdl_mixer(mingw32).

### macOS
- Install sdl2, sdl2_image, sdl2_ttf and sdl2_mixer using the homebrew package manager.

Run - `make` to build the game normally, - `make -j` for compiling on multiple cores and optionally add `debug` to enable the `-g` flag and include the debug prints/features in the executable.

## Running
Currently only runs when executed from the bin directory. This is because it currently relies on its working environment being its the same directory as its assets.
For example; executing it with `./bin/output.exe` would prevent it from finding its assets but `./output.exe` works.

## Design notes
Despite the numerous warnings I read online about the entity component system I decided to attempt to structure my game that way.
As such, everything visible except the cursor and the background are "entities" and those entities are only visible if they implement the Render component.
To put this in simple terms; each entity has a static array of function pointers called components.

```C
typedef struct Entity {  
    SDL_Texture* texture;
    Mix_Chunk* sounds[4];
    SDL_Rect position;
    Component components[COMPONENT_TOTAL];
    Timer* timers;
    bool remove;
} Entity;
```

A component looks like this:

```C
typedef struct Component {
    void (*call)(); 
} Component;
```

This corresponds to an enum with some generic (not finalized) labels.

```C
typedef enum ComponentType {
    Render,
    OnTick,
    LeftClicked,
    RightClicked,
    Dragged,
    Moved,
    Deleted,
    Specific,
    COMPONENT_TOTAL,
} ComponentType;
```

This proves a simple way to change functionality between entities whilst using the same struct.

One of the simplest examples of this is going back to the render function.
Assuming the data structure we chose to hold our entities can be iterated over in a for loop, we can render all the entities easily like;

```C
for (entity in entities) {
  // Does this entity implement the Render component?
  if (hasComponent(entity, Render)) {
    entity.components[Render].call();
  }
}
```

This concept expands to the OnTick component for changing state and the various other generic types.
 
 
