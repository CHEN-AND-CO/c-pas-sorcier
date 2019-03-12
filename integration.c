#include "integration.h"

void integrationTest(int regul,temp_t tInit,int nIterations){
    temp_t temperature = tInit;
    float csgn = consigne(0.0), puissance;
    int tab_len = 1;
    float *tab_temp = malloc(tab_len*sizeof(float *));

	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
	int i=0; // increment de boucle
	
    tab_temp[0] = temperature.interieure;
 
    do {
        visualisationT(temperature);
        csgn = consigne(csgn);

        tab_temp = realloc(tab_temp, ++tab_len*sizeof(float *));
        tab_temp[tab_len-1]=temperature.interieure;
        
        puissance = regulation_pid_de_ses_morts(regul, csgn,tab_temp[i-1], tab_temp[i]);
        visualisationC(puissance);
        temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement
    }while(i++<nIterations);
}
