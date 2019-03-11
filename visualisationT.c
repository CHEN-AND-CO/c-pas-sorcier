#include "visualisationT.h"

/** 
 * visualisationT
 * Send temperatures to external GUI via a file
*/
void visualisationT(temp_t t)
{
    // char *line[MAX_BUFER_SIZE] = {0};

    //Checking for lockfile
    if ( access("interface/.verrouData", F_OK) != -1 )
    {
        printf("[ERROR] File %s locked\n", DATA_PATH);
    } else {
        FILE *lock = fopen(LOCK_PATH, "w"); // Crée le verrou d'accès
        FILE *fTemp = fopen(DATA_PATH, "r+");

        if ( !fTemp ) {
            printf("[ERROR] Failed to open file 'data.txt'\n");
            return;
        }

        fseek(fTemp, 0, SEEK_SET);  //Set cursor to file beginning
        fprintf(fTemp, "%.1f\n%.1f\n", t.exterieure, t.interieure);

        fclose(fTemp);
        fclose(lock); // Suppression pointeur de fichier

        remove(LOCK_PATH); // On retire le verrou
    }
}
