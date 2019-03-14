#include "regulation.h"
	

float regulationTest(int regul, float csgn, float *tabT, int nT) {
	float cmd=100.0;
	int i;

	for (i = 1; i < nT; i++)
	{
		cmd = regulation(10+regul, csgn, tabT[i], tabT[i-1]);
	}

	return cmd;
}

float regulation(int mode, float target, float temp, float prev_temp) {
	switch(mode) {
		case 1: case 11: // ToR
			return (temp < target) ? TOR_FULL_POWER : TOR_LOW_POWER;
		break;

		case 2: // Optimized PID
			return regulation_pid(target, temp, prev_temp);
		break;

		case 12: // Normal PID for automatic test
			return regulation_pid_test(target, temp, prev_temp);
		break;

		default:
			fprintf(stderr, "Error : mode %d is invalid !", mode);

			return 0;
		break;
	}
}

float regulation_pid(float target, float temp, float prev_temp){
	float pid = 0, p,i,d;

	p = PID_OPT_KP * (target - temp); // Kp*(erreur)
	i = PID_OPT_KI * regulation_error_sum(target, temp); // Ki*(somme erreurs)
	d = PID_OPT_KD * (prev_temp - temp); // Kd*(erreur-erreur_precedente)
	pid = p+i+d;

	if (pid < 0) {
		pid = 0;
		regulation_error_sum(-target, -temp); // Substract error to mitigate the impact of saturated errors in the Integrative factor
	} else if (pid > 100) {
		pid = 100;
		regulation_error_sum(-target, -temp); // Substract error to mitigate the impact of saturated errors in the Integrative factor
	}

	printf("T:%.4f\tC:%.4f\tP:%.4f\tI:%.4f\tD:%.4f\tOut:%.4f\n\n", target, temp, p, i, d, pid);

	return pid;
}

float regulation_error_sum(float target, float current) {
	static float i = 0;

	return i += (target - current);
}

float regulation_pid_test(float target, float temp_now, float temp_prev){
	static float i = 0;
	float pid;
	float error = target - temp_now;
	float error_prev = target - temp_prev;

	i += (SAMPLE_RATE*error+(SAMPLE_RATE*(error_prev-error))/2);

	pid = 	PID_KP*error 
			+ PID_KI*i 
			+ PID_KD*(error-error_prev)/SAMPLE_RATE;

	if(pid<0){
		pid = 0;
	}else if(pid>100){
		pid = 100;
	}

	return pid;
}