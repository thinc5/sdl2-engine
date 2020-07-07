# SDL2 based 2D Game Engine

## About
I've always been interested in video games and I figured it was time to attempt to write my own (engine).
I chose SDL2 as my starting point as it was written in C, is cross platform and has lots of documentation.
C was my first choice of language for its potential, performance and flexibility in code structure.
In all honesty, I just want to improve my skills with the language, make a few silly games and have fun in the process!

## Compilation

### Linux
- Install sdl2-dev, sdl2-image, sdl2-ttf and sdl2-mixer from your package manager.

### Windows
- Requires mingw32, gcc, make, sdl2(mingw32), sdl_image(mingw32), sdl_ttf(mingw32) and sdl_mixer(mingw32).

### macOS
- Install sdl2, sdl2_image, sdl2_ttf and sdl2_mixer using the homebrew package manager.

Run - `make` to build the game normally, - `make -j` for compiling on multiple cores and optionally add `debug` to enable the `-g` flag and include the debug prints/features in the executable.

## Running
Just click on the binary (graphical) or run from the terminal from anywhere on your system.

## Status
I occasionally find time to work on it, and there are many design decisions which I am not happy with (In retrospect).
An implementation of snake is almost complete, so that would probably take precident over any further engine changes.
