#include "regulation.h"
	
float regulationTest(int regul,float csgn,float* tabT, int nT){
	float cmd=100.0;
	
	cmd = regulation(regul, csgn, tabT, nT);

	return cmd;
}

float regulation(int mode, float target, float *tab_temp, int tab_len){
	switch(mode){
		case 1: // ToR
			return (tab_temp[tab_len-1] < target)? TOR_FULL_POWER:TOR_LOW_POWER;
		break;
		case 2: // PID
			float p = PID_KP*(target-tab_temp[tab_len-1]); // Kp*(erreur)
			float i = PID_KI*regulation_error_sum(target, tab_temp, tab_len); // Ki*(somme erreurs)
			float d = PID_KD*(tab_temp[tab_len-1]+tab_temp[tab_len-2]); // Kd*(erreur-erreur_precedente)

			return p+i+d;
		break;
		default:
			fprintf(stderr, "Error : mode %d is invalid !", mode);

			return 0;
		break;
	}
}

float regulation_error_sum(float target, float *tab_temp, int tab_len){
	float error = 0;

	while(tab_len>0){
		error += (target-tab_temp[--tab_len]);
	}

	return error;
}