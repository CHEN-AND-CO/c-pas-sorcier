#include "integration.h"

void integrationTest(int regul, temp_t tInit, int nIterations)
{
    float csgn = 0, puissance;                         // Target temperature and power command
    int tab_len = 1;                                   // History length
    float *tab_temp = malloc(tab_len * sizeof(float)); // Allocate the history into the memory

    struct simParam_s *monSimulateur_ps = simConstruct(tInit); // create the simulator
    int i = 1;                                                 // counter

    tab_temp[0] = tInit.interieure; // Add the initial inside temperature to the history

    do
    {
        visualisationT(tInit); // Write the current temperatures into the data file
        csgn = consigne(csgn); // Read the target temperature from the consigne file

        tab_temp = realloc(tab_temp, ++tab_len * sizeof(float)); // Expand the history
        tab_temp[tab_len - 1] = tInit.interieure;                // Add the current inside temperature to the history

        puissance = regulation(regul, csgn, tab_temp[i - 1], tab_temp[i]); // Get the power needed for temperature regulation
        visualisationC(puissance);                                         // Write the power command
        tInit = simCalc(puissance, monSimulateur_ps);                      // Environment simulation
    } while (i++ < nIterations);

    simDestruct(monSimulateur_ps); // Delete the simulator
    free(tab_temp);                // Clear from the memory the history
}
