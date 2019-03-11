PROJET = c-pas-sorcier

CFLAGS = -g -Wall -Wextra -Os -std=gnu11
LDFLAGS = -lm #-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx -lm -lGL -lGLU

SRC = $(wildcard *.c)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))

all: $(PROJET)

remake: clean $(PROJET)

$(PROJET) : $(OBJ)
	gcc obj/* $(LDFLAGS) -o $@

obj/%.o: %.c
	gcc -c $< -I. -o $@ $(CFLAGS)

clean:
	rm obj/*.o *.out *.gch -f

clear:
	rm obj/*.o *.gch -f