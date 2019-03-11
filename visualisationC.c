#include "visualisationC.h"

void visualisationC(float puissance_f)
{
   if(access(LOCK_PATH, F_OK) != -1){ // Vérifie si le fichier est disponible      
        fprintf(stderr, "File %s is locked !", CONSIGNE_PATH);
   }else{
        FILE *lock = fopen(LOCK_PATH, "w"); // Crée le verrou d'accès
        FILE *sum_file_pointer = fopen(CONSIGNE_PATH, "w+"); // Ouvre le fichier de consigne

        if(!sum_file_pointer){ // Vérifie si on a réussi à ouvrir le fichier
           fprintf(stderr, "Failed to open %s !", CONSIGNE_PATH);

           return;
        }

        char str_pui[MAX_BUFFER_SIZE] = {0}; //Chaine pour consigne de puissance
        snprintf(str_pui, MAX_BUFFER_SIZE, "%f", puissance_f); // Conversion float vers string
        if(fputs(str_pui, sum_file_pointer)==-1){ //Si l'écriture rate
            fprintf(stderr, "Failed to write on %s !", CONSIGNE_PATH);    
        }

        fclose(sum_file_pointer); // Suppression pointeur de fichier
        fclose(lock); // Suppression pointeur de fichier

        remove(LOCK_PATH); // On retire le verrou
   }
}
