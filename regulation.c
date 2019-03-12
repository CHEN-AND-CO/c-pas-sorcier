#include "regulation.h"
	

float regulationTest(int regul, float csgn, float *tabT, int nT) {
	float cmd=100.0;
	
	for(size_t i = 1; i < nT; i++)
	{
		cmd = regulation(regul, csgn, tabT[i], tabT[i-1]);
	}

	return cmd;
}

float regulation(int mode, float target, float temp, float prev_temp) {
	float p,i,d, pid;	

	switch(mode) {
		case 1: // ToR
			return (temp < target) ? TOR_FULL_POWER : TOR_LOW_POWER;
		break;

		case 2: // PID
			p = PID_KP * (target - temp); // Kp*(erreur)
			i = PID_KI * regulation_error_sum(target, temp); // Ki*(somme erreurs)
			d = PID_KD * (prev_temp - temp); // Kd*(erreur-erreur_precedente)
			pid = p+i+d;

			if (pid < 0) {
				pid = 0;
				regulation_error_sum(target, - temp); // Substract error to mitigate the impact of saturated errors in the Integrative factor
			} else if (pid > 100) {
				pid = 100;
				regulation_error_sum(target, - temp); // Substract error to mitigate the impact of saturated errors in the Integrative factor
			}

			return pid;
		break;

		default:
			fprintf(stderr, "Error : mode %d is invalid !", mode);

			return 0;
		break;
	}
}

float regulation_error_sum(float target, float current) {
	static float i = 0;

	i += (target - current);

	return i;
}