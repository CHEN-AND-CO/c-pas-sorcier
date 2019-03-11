#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_LOCK_PATH ".verrouData"
#define CONSIGNE_LOCK_PATH ".verrouConsigne"
#define DATA_PATH "data.txt"
#define CONSIGNE_PATH "consigne.txt"
#define MAX_BUFFER_SIZE 4096

typedef struct {
	float interieure;
	float exterieure;
}temp_t;

#endif /* DEFINE_H */