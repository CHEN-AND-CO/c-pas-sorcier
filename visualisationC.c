#include "visualisationC.h"

void visualisationC(float puissance_f)
{
   if(access(".verrouData", F_OK) != -1){        
        fprintf(stderr, "File %s is locked !", CONSIGNE_PATH);
   }else{
        FILE *sum_file_pointer = fopen(CONSIGNE_PATH, "w+");

        if(!sum_file_pointer){
           fprintf(stderr, "Failed to open %s !", CONSIGNE_PATH);

           return;
        }

        char *str_pui = malloc(MAX_BUFFER_SIZE*sizeof(char *));
        snprintf(str_pui, MAX_BUFFER_SIZE, "%f", puissance_f);
        if(fputs(str_pui, sum_file_pointer)==-1){
            fprintf(stderr, "Failed to write on %s !", CONSIGNE_PATH);    
        }
   }
}
