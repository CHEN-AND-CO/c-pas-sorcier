#include "visualisationT.h"

void visualisationT(temp_t t)
{
    if ( access("interface/.verrouData", F_OK) != -1 )
    {
        FILE *fTemp = fopen("interface/data.txt", "w");

        if ( !fTemp ) {
            printf("[ERROR] Failed to open file 'data.txt'\n");
        } else {
            fprintf(fTemp, "%.1f\n%.1f\n", t.exterieure, t.interieure);
        }
    } else {
        printf("[ERROR] File 'data.txt' locked\n");
    }
}
