#include "regulation.h"
	

float regulationTest(int regul,float csgn,float* tabT, int nT){
	float cmd=100.0;
	
	cmd = regulation(regul, csgn, tabT, nT);

	return cmd;
}

float regulation(int mode, float target, float *tab_temp, int tab_len){
	float p,i,d, pid;
	
	switch(mode){
		case 1: // ToR
			return (tab_temp[tab_len-1] < target) ? TOR_FULL_POWER : TOR_LOW_POWER;
		break;
		case 2: // PID
			p = PID_KP*(target-tab_temp[tab_len-1]); // Kp*(erreur)
			i = PID_KI*regulation_error_sum(target, tab_temp[tab_len-1]); // Ki*(somme erreurs)
			d = PID_KD*(tab_temp[tab_len-2]-tab_temp[tab_len-1]); // Kd*(erreur-erreur_precedente)
			pid = p+i+d;

			if (pid < 0) {
				pid = 0;
				regulation_error_sum(target, -tab_temp[tab_len - 1]); // Substract error to mitigate the impact of saturated errors in the Integrative factor
			} else if (pid > 100) {
				pid = 100;
				regulation_error_sum(target, -tab_temp[tab_len - 1]); // Substract error to mitigate the impact of saturated errors in the Integrative factor
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