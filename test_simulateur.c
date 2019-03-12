#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "visualisationT.h"
#include "integration.h"

int main(){

	temp_t temperature;
	temperature.exterieure = 14.0;
	temperature.interieure = 15.0;
	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
	int i=0; // increment de boucle
	float puissance = 70.0; // puissance de chauffage
	
	int tab_len = 1;
    float *tab_temp = malloc(tab_len*sizeof(float *));
    float csgn = 0.0;

    tab_temp[0] = temperature.interieure;

	///////////////////////////////////////////////////
	//   REMOVE THIS
	FILE *fLog = initLogger();
	//////////////////////////



    csgn = consigne(0.0);
    puissance = regulation(2, csgn, tab_temp, tab_len, fLog);
	/////////////////////////////////////////////////////////
       
	
	for(i=0;1;i++){
		temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement
		
		tab_temp = realloc(tab_temp, ++tab_len*sizeof(float *));
        tab_temp[tab_len-1]=temperature.interieure;
        csgn = consigne(0.0);

        puissance = regulation(2, csgn, tab_temp, tab_len, fLog);
		/////////////////////////////////////////////////////////
        
		visualisationC(puissance);
		visualisationT(temperature);

		usleep(50000);
	}

	simDestruct(monSimulateur_ps); // destruction de simulateur

	stopLogger(fLog);
	/////////////////
	return EXIT_SUCCESS;
}
