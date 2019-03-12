#ifndef REGULATION_H 
#define REGULATION_H

#include "define.h" 

#define TOR_LOW_POWER 0
#define TOR_FULL_POWER 40

#define PID_KP 1
#define PID_KI 0.1
#define PID_KD 0.1

float regulationTest(int regul,float csgn,float* tabT, int nT, FILE *fLog);

float regulation(int mode, float target, float *tab_temp, int tab_len, FILE *fLog);

float regulation_error_sum(float target, float current);


FILE *initLogger();
void logPID(FILE *fLog, float setpoint, float current, float p, float i, float d, float output);
void stopLogger(FILE *fLog);

#endif /* REGULATION_H */
