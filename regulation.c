#include "regulation.h"
	

float regulationTest(int regul,float csgn,float* tabT, int nT, FILE *fLog){
	float cmd=100.0;
	
	cmd = regulation(regul, csgn, tabT, nT, fLog);

	return cmd;
}

float regulation(int mode, float target, float *tab_temp, int tab_len, FILE *fLog){
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
				regulation_error_sum(-target, -tab_temp[tab_len-1]); // Substract error to mitigate the impact of saturated errors in the Integrative factor
			} else if (pid > 100) {
				pid = 100;
				regulation_error_sum(-target, -tab_temp[tab_len-1]); // Substract error to mitigate the impact of saturated errors in the Integrative factor
			}

			logPID(fLog, target, tab_temp[tab_len-1], p, i, d, pid);

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



FILE *initLogger() {
	FILE *fLog = NULL;

	if (fLog = fopen("pid.log", "w")) return fLog;
	else {
		perror("Unable to open log file 'pid.log'\n");
		return NULL;
	}
}

void logPID(FILE*fLog, float setpoint, float current, float p, float i, float d, float output) {
	fprintf(fLog, "%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n", setpoint, current, p, i, d, output);
	printf("%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n", setpoint, current, p, i, d, output);
}

void stopLogger(FILE *fLog) {
	fclose(fLog);
	free(fLog);
}