PROJET = c-pas-sorcier

CFLAGS = -g -Wall -Wextra -Os -std=gnu11
LDFLAGS = -lm #-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx -lm -lGL -lGLU

SRC = $(wildcard src/*.c)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))

all: $(PROJET)

remake: clean $(PROJET)

$(PROJET) : $(OBJ)
	gcc *.o $(LDFLAGS) -o $@

obj/%.o: %.c
	gcc -c $< -I. -o $@ $(CFLAGS)

clean:
	rm *.o *.out *.gch -f

clear:
	rm *.o *.gch -f