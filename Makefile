# executable name

TARGET			= output.out

# compiler to use
CC			= gcc

# compiler flags
CFLAGS   		= -std=c99 -pedantic -Wall -g

LINKER   		= gcc

# linking flags
LFLAGS			= -Isrc/include -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# directories
SRCDIR   = src
INCDIR   = include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(shell du -a $(SRCDIR) | grep -E '\.(c)$$' | awk '{print $$2}')
INCLUDES := $(shell du -a $(INCDIR) | grep -E '\.(h)$$' | awk '{print $$2}')
XTRADIR  := $(shell ls -l include/ | grep "^d" | awk -F" " '{print $$9}')

$(info $(SOURCES))

OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -rf


$(shell mkdir -p $(OBJDIR) $(XTRADIR))

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo $(SOURCES) $(INCLUDES) $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
