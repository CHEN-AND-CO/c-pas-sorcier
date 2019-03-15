#include "visualisationT.h"

/** 
 * visualisationT
 * Send temperatures to external GUI via a file
*/
void visualisationT(temp_t t)
{
    FILE *fTemp = NULL;

    //Checking for lockfile
    if (access(DATA_LOCK_PATH, F_OK) != -1)
    {
        printf("[ERROR] File %s locked\n", DATA_PATH);
    }
    else
    {
        FILE *lock = fopen(DATA_LOCK_PATH, "w"); // Crée le verrou d'accès

        if (access(DATA_PATH, F_OK) == -1) {
            fTemp = fopen(DATA_PATH, "w+"); // Create the data file
            fputs("0.0\n0.0\ntrue\n", fTemp);

            fclose(fTemp);
        } 

        #ifdef __linux__
            fTemp = fopen(DATA_PATH, "r+"); // Open the data file
        #else
            fTemp = fopen(DATA_PATH, "w+"); // Open the data file
        #endif

        if (!fTemp)
        {
            printf("[ERROR] Failed to open file 'data.txt'\n");

            fclose(lock);
            remove(DATA_LOCK_PATH);

            return;
        }

        fseek(fTemp, 0, SEEK_SET); //Set cursor to file beginning
        fprintf(fTemp, "%.1f\n%.1f\n", t.exterieure, t.interieure);

        fclose(fTemp);
        fclose(lock); // Remove the file pointer

        remove(DATA_LOCK_PATH); // Delete the lock file
    }
}
