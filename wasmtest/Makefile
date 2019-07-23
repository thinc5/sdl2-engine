rm				:= rm -rf
mkdir			:= mkdir -p
findc			:= du -a $(SRCDIR) | grep -E '\.(c)$$' | awk '{print $$2}'
findh			:= du -a $(INCDIR) | grep -E '\.(h)$$' | awk '{print $$2}'

SRCDIR   		:= .
INCDIR			:= .
OBJDIR			:= obj

TARGET = index.js

CC = emcc

CFLAGS = --use-preload-plugins -DEMSCRIPTEN -O3 -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 #-s USE_SDL_MIXER=2
LFLAGS = -DEMSCRIPTEN -O3 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 #-s USE_SDL_MIXER=2

SOURCES  		:= $(shell $(findc))
INCLUDES 		:= $(shell $(findh))


OBJECTS  		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# make subfolders if they do not already exist.
#XTRADIR  := $(shell ls -d $(INCDIR)/*/ | sed 's/$(INCDIR)/$(OBJDIR)/g')
$(shell $(mkdir) $(OBJDIR)) #(XTRADIR))

all: build

debug: CFLAGS += -DDEBUG -g
debug: build

build: $(OBJECTS) $(TARGET)

# compile objects.
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(info Compiled $<)

# link objects.
$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@
	$(info Linking complete!)

