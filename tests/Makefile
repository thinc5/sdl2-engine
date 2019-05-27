# Hacked together stripped down makefile for building our tests.

#-------------- Variables
# determine os
UNAME			= $(shell uname)
OS				=
# compiler to use
CC				:= g++
# compiler flags
CFLAGS   		:= -std=c++17 -Wall -pedantic
# linker to use
LINKER   		:= g++
# linking flags
LFLAGS			:= -Isrc/include -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lgtest
# directories
SRCDIR   		:= .

#-------------- Helper scripts
rm			:= rm -rf
mkdir			:= mkdir -p
findc			:= du -a $(SRCDIR) | grep -E '\.(cpp)$$' | awk '{print $$2}'


OS				= UNIX

#-------------- Populate build sources
SOURCES  		:= $(shell $(findc))

# What are my objects?
OBJECTS  		:= $(SOURCES:$(SRCDIR)/%.cpp=$(SRCDIR)/%.out)

#-------------- Rules
# default rules
all: build

# compile and link
build: $(OBJECTS)

# rebuild.
rebuild: clean
	$(MAKE) build

# compile objects.
$(OBJECTS): $(OBJDIR)/%.out : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) $(LFLAGS) $(SOURCES) $< -o $@
	$(info Compiled $<)

.PHONY:	clean

# clean all building materials.
clean:
	@$(rm) *.out
	@echo "Executable/s removed!"
