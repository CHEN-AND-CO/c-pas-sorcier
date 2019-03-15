#include "integration.h"

int main()
{
    temp_t temperature = {16.0, 14.0};
    int mode_regul = NORMAL_PID; // Mode de régulation

    int i = 1;                                         // increment de boucle
    int tab_len = 1;                                   // Nb d'elements de tab_temp
    float *tab_temp = malloc(tab_len * sizeof(float)); //Contient tous les t_int

    struct simParam_s *monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%

    float csgn = 5.0, puissance = 70.0; // Consigne et Puissance par defaut

    tab_temp[0] = temperature.interieure; // Ajout de la 1er valeur de t_int
    do
    {
        visualisationT(temperature); // Récupération des températures
        csgn = consigne(csgn);       // Récupération de la consigne

        tab_temp = realloc(tab_temp, ++tab_len * sizeof(float)); // Réallocation en mémoire du tableau
        tab_temp[tab_len - 1] = temperature.interieure;          // Ajout de la valeur de température intérieure

        puissance = regulation(mode_regul, csgn, tab_temp[i - 1], tab_temp[i]); // Régulation
        visualisationC(puissance);                                              //MaJ Commande chauffage (true/false)
        temperature = simCalc(puissance, monSimulateur_ps);                     // simulation de l'environnement

        WAIT_MS(100);
    } while (csgn > MIN_TARGET && i++); //Tant que la consigne > 5°c on incrémente i

    simDestruct(monSimulateur_ps); // Suppression du simulateur
    free(tab_temp);                // Libération du tableau des températures

    return EXIT_SUCCESS;
}
