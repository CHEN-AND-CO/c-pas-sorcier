#include "define.h"
#include "simulateur.h"
#include "consigne.h"
#include "regulation.h"
#include "visualisationT.h"
#include "visualisationC.h"
#include "usb.h"

int main(){
    temp_t temperature = {16.0, 14.0};

    float csgn = consigne(0.0), puissance;
    
    int tab_len = 1, regul_mode = 2;
    float *tab_temp = malloc(tab_len*sizeof(float));

	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
	int i=1; // increment de boucle
	
    tab_temp[0] = temperature.interieure;
 
    do {
        visualisationT(temperature);
        csgn = consigne(csgn);

        tab_temp = realloc(tab_temp, ++tab_len*sizeof(float));
        tab_temp[tab_len-1]=temperature.interieure;
        
        puissance = regulation(regul_mode, csgn,tab_temp[i-1], tab_temp[i]);
        visualisationC(puissance);
        temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement

        i++;
        usleep(70000);
    }while(csgn>5);

    simDestruct(monSimulateur_ps);
    free(tab_temp);

    return 0;
}