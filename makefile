# 

PROJET = c-pas-sorcier

ifeq ($(OS),Windows_NT)     					# Windows OS
    detected_OS := Windows
else
    detected_OS := $(shell uname) 				# Unix Based OS
endif

CC = gcc
CFLAGS = -g -Wall -Wextra -Os -std=gnu11		# Compiler flags
LDFLAGS = -lm									# Libs for all systems

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
	$(CC) $(OBJ) $(LDFLAGS) -o $@

obj/%.o: %.c
	$(CC) -c $< -I. -o $@ $(CFLAGS)

clean:
	rm $(OBJ) $(PROJET) obj/*.gch -f

clear:
	rm $(OBJ) obj/*.gch -f
