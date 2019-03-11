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
        printf("[ERROR] File 'data.txt' locked\n");
    } else {
        FILE *fTemp = fopen("interface/data.txt", "a+");

        if ( !fTemp ) {
            printf("[ERROR] Failed to open file 'data.txt'\n");
            return;
        }

        fseek(fTemp, 0, SEEK_SET);  //Set cursor to file beginning
        fprintf(fTemp, "%.1f\n%.1f\n", t.exterieure, t.interieure);

        fclose(fTemp);
    }
}
