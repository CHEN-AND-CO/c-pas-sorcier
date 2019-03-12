#include "integration.h"

void integrationTest(int regul,temp_t tInit,int nIterations){
    temp_t temperature = tInit;
	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
	int i=0; // increment de boucle
	int tab_len = 1;
    float *tab_temp = malloc(tab_len*sizeof(float *));
    
    float csgn = consigne(0.0);
    float puissance = regulation(2, csgn, tab_temp, tab_len); // puissance de chauffage
    tab_temp[0] = temperature.interieure;
	
	for(i=0;i<nIterations;i++){
		temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement
		
		tab_temp = realloc(tab_temp, ++tab_len*sizeof(float *));
        tab_temp[tab_len-1]=temperature.interieure;
        csgn = consigne(0.0);
        puissance = regulation(2, csgn, tab_temp, tab_len);
   
		visualisationC(puissance);
		visualisationT(temperature);

        //usleep(100000);
	}
}
