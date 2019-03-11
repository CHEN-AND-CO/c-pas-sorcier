#include "visualisationC.h"

void visualisationC(float puissance_f)
{
   if(access(".verrouData", F_OK) != -1){
       FILE *sum_file_pointer = fopen(DATA_PATH, "a+");

       if(!sum_file_pointer){
           fprintf(stderr, "Failed to open %s !", DATA_PATH);

           return;
       }

        char buffer[MAX_BUFFER_SIZE] = {0};
        float puis = atof(fgets(buffer, MAX_BUFFER_SIZE, sum_file_pointer));
        
        
   }else{
       fprintf(stderr, "File %s doesn\'t exist !", DATA_PATH);
   }
}
