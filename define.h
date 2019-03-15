#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_LOCK_PATH ".verrouData"		 // Path for the lock of data
#define CONSIGNE_LOCK_PATH ".verrouConsigne" // Path for the lock of consigne
#define DATA_PATH "data.txt"				 // Path for the data file
#define CONSIGNE_PATH "consigne.txt"		 // Path for the consigne file
#define MAX_BUFFER_SIZE 4096				 //

#define WAIT_MS(x) 												\
	struct timespec tms1 = {x/1000, (x%1000)*1000000}, tms2; 	\
	nanosleep(&tms1, &tms2);										\

typedef struct
{
	float interieure;
	float exterieure;
} temp_t;

#endif /* DEFINE_H */