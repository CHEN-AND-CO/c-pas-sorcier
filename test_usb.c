#include "define.h"
#include "simulateur.h"
#include "consigne.h"
#include "regulation.h"
#include "visualisationT.h"
#include "visualisationC.h"
#include "usb.h"
#include "releve.h"
#include "commande.h"
#include <unistd.h>

int main()
{
    temp_t temperature = {16.0, 14.0};                  // Initial temperatures
    float csgn = 100, puissance;                        // Target temperature and power command
    int tab_len = 1, regul_mode = NORMAL_PID;           // History length and regulation mode                
    float *tab_temp = malloc(tab_len * sizeof(float));  // History

    int i = 1;                                          // Loop counter
    FILE *trace = fopen(TRACE_PATH, "w+");              // Open the trace file

    if (!trace)                                         // Failure
    {
        fprintf(stderr, "Impossible to create %s\n", TRACE_PATH);
    }

    tab_temp[0] = temperature.interieure;               // Add initial temperature to the history

    do
    {
        temperature = releve();                         // Get the current temperatures through USB
        visualisationT(temperature);                    // Write the current temperatures into data
        csgn = consigne(csgn);                          // Get the current temperature target from consigne
        if(trace) {                                     // If trace file opened
            fprintf(trace, "%f,%f,%f,%f\n", i * SAMPLE_RATE, 0.0, temperature.exterieure, temperature.interieure);
        }        

        tab_temp = realloc(tab_temp, ++tab_len * sizeof(float)); // Allocate more space for the history
        tab_temp[tab_len - 1] = temperature.interieure;          // Add the current inside temperature

        puissance = regulation(regul_mode, csgn, tab_temp[i - 1], tab_temp[i]); // Get the regulated power command 
        visualisationC(puissance); //Write the power status

        commande(puissance); // Send the power command through USB

        i++;
        //WAIT_MS(200);
    } while (csgn > MIN_TARGET);

    free(tab_temp); // Clear the history from memory
    if(trace){
        fclose(trace); // Close the trace file
    }

    return 0;
}