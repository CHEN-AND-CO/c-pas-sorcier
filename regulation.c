#include "regulation.h"
	
float regulationTest(int regul,float csgn,float* tabT, int nT){
	float cmd=100.0;

	for(int i=0; i<nT; i++){
		cmd = regulation(regul, csgn, tabT[i]);
	}

	return cmd;
}

float regulation(int mode, float target, float temp){
	switch(mode){
		case 1: // ToR
			return (temp < target)? TOR_FULL_POWER:TOR_LOW_POWER;
		break;
		case 2: // PID
			
		break;
		default:
			fprintf(stderr, "Error : mode %d is invalid !", mode);

			return 0;
		break;
	}
}
