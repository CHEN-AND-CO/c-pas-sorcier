#ifndef REGULATION_H 
#define REGULATION_H

#include "define.h" 

#define TOR_LOW_POWER 0
#define TOR_FULL_POWER 40

float regulationTest(int regul,float csgn,float* tabT, int nT);

float regulation(int mode, float target, float temp);

#endif /* REGULATION_H */
