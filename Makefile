# copied from stack overflow lol cant
# remember where but not original makefile

# executable name
TARGET_LINUX   = output

TARGET_WINDOWS = output.exe

# compiler to use
CC_LINUX       = gcc

CC_WINDOWS     = x86_64-w64-mingw32-gcc

CC_WASM        = emcc

# compiler flags here
CFLAGS   = -std=c99 -Wall -g

LINKER_LINUX   = gcc

LINKER_WINDOWS = x86_64-w64-mingw32-gcc

WASM_FLAGS     = -s WASM=1

# linking flags here
LFLAGS_LINUX   = -Isrc/include -lSDL2 -lSDL2_image

LFLAGS_WINDOWS = -Isrc/include

# directories
SRCDIR   = src
INCDIR   = include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET_LINUX): $(OBJECTS)
	@echo $(SOURCES) $(INCLUDES) $(OBJECTS)
	@$(LINKER_LINUX) $(OBJECTS) $(LFLAGS_LINUX) -o $@
	@echo "Linking complete!"

# $(BINDIR)/$(TARGET_WINDOWS): $(OBJECTS)
# 	@echo $(SOURCES) $(INCLUDES) $(OBJECTS)
# 	@$(LINKER_WINDOWS) $(OBJECTS) $(LFLAGS_WINDOWS) -o $@
# 	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC_LINUX) $(CFLAGS) -c $< -o $@
	# @$(CC_WINDOWS) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET_LINUX)
	@$(rm) $(BINDIR)/$(TARGET_WINDOWS)
	@echo "Executable removed!"