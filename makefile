# 

EXE_1 = test_simulateur
EXE_2 = test_usb

ifeq ($(OS),Windows_NT)     					# Windows OS
    detected_OS := Windows
else
    detected_OS := $(shell uname) 				# Unix Based OS
endif

ifeq ($(CC), cc)
	CC = gcc
endif

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
OBJ = $(subst obj/$(EXE_2).o,,$(subst obj/$(EXE_1).o,,$(addprefix obj/, $(addsuffix .o, $(NOM)))))

all: $(EXE_1) $(EXE_2)

remake: clean $(EXE_1) $(EXE_2)

$(EXE_1): $(OBJ) obj/$(EXE_1).o
	$(CC) $(OBJ) obj/$(EXE_1).o $(LDFLAGS) -o $@

$(EXE_2): $(OBJ) obj/$(EXE_2).o
	$(CC) $(OBJ) obj/$(EXE_2).o $(LDFLAGS) -o $@

obj/%.o: %.c
	$(CC) -c $< -I. -o $@ $(CFLAGS)

clean:
	rm $(OBJ) obj/$(EXE_1).o obj/$(EXE_2).o $(EXE_1) $(EXE_2) obj/*.gch -f

clear:
	rm $(OBJ) obj/$(EXE_1).o obj/$(EXE_2).o obj/*.gch -f
