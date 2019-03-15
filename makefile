# Makefile by Kévin Le Torc'h

EXE_1 = test_simulateur
EXE_2 = test_usb

ifeq ($(OS),Windows_NT)     					# Windows OS
    detected_OS := Windows
else
    detected_OS := $(shell uname) 				# Unix Based OS
endif

ifeq ($(CC),cc)									# If CC set to "cc"				
	CC = gcc									# Forced to "gcc"
endif
ifeq ($(CC),)									# If no c compiler set
	CC = gcc									# Forced to "gcc"
endif

INCLUDES = -I. -Ilib							# include folders
CFLAGS = -g -Wall -Wextra -Os -std=gnu11		# Compiler flags
LDFLAGS = -lm -ansi								# Libs for all systems

ifeq ($(detected_OS),Windows)
    LDFLAGS += -Llib -l:ftd2xx.lib
	EXTENSION = .exe
	DELETE_CMD = del
else
    LDFLAGS += -Llib -lftd2xx
	EXTENSION =
	DELETE_CMD = rm
endif

SRC = $(wildcard *.c)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(subst $(EXE_2).o,,$(subst $(EXE_1).o,, $(addsuffix .o, $(NOM))))

all: $(EXE_1)$(EXTENSION) $(EXE_2)$(EXTENSION)				# Build all executables

rebuild: remake												# Clean and build all executables

remake: clean $(EXE_1)$(EXTENSION) $(EXE_2)$(EXTENSION)		# Same as rebuild

$(EXE_1)$(EXTENSION): $(OBJ) $(EXE_1).o
	$(CC) $(OBJ) $(EXE_1).o $(LDFLAGS) -o $@

$(EXE_2)$(EXTENSION): $(OBJ) $(EXE_2).o
	$(CC) $(OBJ) $(EXE_2).o $(LDFLAGS) -o $@

# Build all the .o files
%.o: %.c
	$(CC) -c $< $(INCLUDES) -o $@ $(CFLAGS)
	
# Remove all files generated by compilation (executables included)
clean:
	$(DELETE_CMD) $(OBJ) $(EXE_1).o $(EXE_2).o $(EXE_1)$(EXTENSION) $(EXE_2)$(EXTENSION) *.gch -f

# Remove all files generated by compilation (except executables)
clear:
	$(DELETE_CMD) $(OBJ) $(EXE_1).o $(EXE_2).o *.gch -f

run-usb: $(EXE_2)$(EXTENSION)
	./$(EXE_2)$(EXTENSION)

run-simu: $(EXE_1)$(EXTENSION)
	./$(EXE_1)$(EXTENSION)

zip-test:
	zip test consigne.* define.h integration.* regulation.* simulateur.* visualisation*

install-libftd2xx:
	sudo cp lib/libftd2xx.so /usr/lib/
	sudo cp lib/libftd2xx.a /usr/lib/
	sudo chmod 0755 /usr/lib/libftd2xx.so
	sudo cp lib/libftd2xx.so /usr/local/lib/
	sudo cp lib/libftd2xx.a /usr/lib/
	sudo chmod 0755 /usr/local/lib/libftd2xx.so