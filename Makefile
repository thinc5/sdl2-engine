#-------------- Variables
# determine os
UNAME			= $(shell uname)
OS				=
# executable name
TARGET			:= output.out
# compiler to use
CC				:= gcc
# compiler flags
CFLAGS   		:= -std=gnu11 -Wall -pedantic
# linker to use
LINKER   		:= gcc
# linking flags
LFLAGS			:= -Isrc/include -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
# directories
SRCDIR   		:= src
INCDIR			:= include
OBJDIR			:= obj
BINDIR			:= bin


#-------------- Helper scripts
rm				:= rm -rf
mkdir			:= mkdir -p
findc			:= du -a $(SRCDIR) | grep -E '\.(c)$$' | awk '{print $$2}'
findh			:= du -a $(INCDIR) | grep -E '\.(h)$$' | awk '{print $$2}'


#-------------- Determine OS
ifeq ($(UNAME), Linux)
OS				= UNIX
else ifeq ($(UNAME), MINGW32_NT-6.2)
OS				= WIN
else ifeq ($(UNAME), Darwin)
OS				= UNIX
else
$(info "Operating system: $(UNAME) not supported at this point in time.")
exit 0
endif

CFLAGS += -D${OS}


# override if on windows
ifeq ($(OS), WIN)
# Not currently needed.
# SHELL 		:= powershell
TARGET			:= output.exe
# where is the find command located on your windows machine?
LFLAGS			:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lshlwapi -Isrc/include
endif

$(info Environment: $(OS))


#-------------- Populate build sources
SOURCES  		:= $(shell $(findc))
INCLUDES 		:= $(shell $(findh))

# What are my objects?
OBJECTS  		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# make subfolders if they do not already exist.
XTRADIR  := $(shell ls -d $(INCDIR)/*/** | sed 's/$(INCDIR)/$(OBJDIR)/g')
$(shell $(mkdir) $(OBJDIR) $(XTRADIR))


#-------------- Rules
# default rules
all: build

# debug build?
debug: CFLAGS += -DDEBUG -g
debug: LFLAGS += -DDEBUG -g
debug: build

# enable profiling with gprof
gprof: CFLAGS += -pg
gprof: LFLAGS += -pg
gprof: build

# compile and link
build: $(OBJECTS) $(BINDIR)/$(TARGET)

# rebuild.
rebuild: clean
	$(MAKE) build

# compile objects.
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(info Compiled $<)


# link objects.
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	$(info Linking complete!)


.PHONY:	clean release

# are we making a release?
ifeq ($(OS), WIN)
release:
	@'C:\Program Files\7-Zip\7z.exe' a -mx=9 release.zip bin\* > /dev/null
else
release:
	@zip bin release.zip
endif

# clean all building materials.
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
