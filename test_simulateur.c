#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "visualisationT.h"
#include "integration.h"

int main(){

	temp_t temperature;
	temperature.exterieure = 14.0;
	temperature.interieure = 15.0;
	
	integrationTest(2, temperature, 9999);
	
	return EXIT_SUCCESS;
}
