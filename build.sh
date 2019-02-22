#!bin/bash

# Very simpple entry point for build env containter.
make clean
#echo "Building sdl2 for cross compilation...."
#cd /dir/extra/SDL2/
#make cross
echo "Building game..."
cd /dir/
make