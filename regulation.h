#ifndef REGULATION_H 
#define REGULATION_H

#include "define.h" 

#define TOR_LOW_POWER 0
#define TOR_FULL_POWER 40

#define PID_KP 1
#define PID_KI 0.1
#define PID_KD 0.1

float regulationTest(int regul,float csgn,float* tabT, int nT);

float regulation(int mode, float target, float temp, float prev_temp);

float regulation_error_sum(float target, float current);

float regulation_pid_de_ses_morts(int mode, float target, float temp_prev, float temp_now);

#endif /* REGULATION_H */
