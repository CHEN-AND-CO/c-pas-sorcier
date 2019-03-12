PROJET = c-pas-sorcier

ifeq ($(OS),Windows_NT)     # Windows
    detected_OS := Windows
else
    detected_OS := $(shell uname)  # Unix Based
endif

CFLAGS = -g -Wall -Wextra -Os -std=gnu11
LDFLAGS = -lm #-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx -lm -lGL -lGLU

ifeq ($(detected_OS),Windows)
    LDFLAGS += ./ftd2xx.lib
endif
ifeq ($(detected_OS),Linux)
    LDFLAGS += -lftd2xx
endif

SRC = $(wildcard *.c)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))

all: $(PROJET)

remake: clean $(PROJET)

$(PROJET) : $(OBJ)
	gcc $(OBJ) $(LDFLAGS) -o $@

obj/%.o: %.c
	gcc -c $< -I. -o $@ $(CFLAGS)

clean:
	rm $(OBJ) $(PROJET) obj/*.gch -f

clear:
	rm $(OBJ) obj/*.gch -f
