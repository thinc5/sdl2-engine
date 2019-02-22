#!bin/bash

# Very simpple entry point for build env containter.
cd dir/
make
make MakeWindows
gdb ./bin/output