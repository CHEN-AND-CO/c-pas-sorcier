#include "consigne.h"

float consigne(float csgn)
{
      if(access(LOCK_PATH, F_OK) != -1){ // Vérifie si le fichier est disponible      
            fprintf(stderr, "File %s is locked !", CONSIGNE_PATH);
      }else{
            FILE *lock = fopen(LOCK_PATH, "w"); // Crée le verrou d'accès
            FILE *sum_file_pointer = fopen(CONSIGNE_PATH, "r+"); // Ouvre le fichier de consigne

            if(!sum_file_pointer){ // Vérifie si on a réussi à ouvrir le fichier
                  fprintf(stderr, "Failed to open %s !", CONSIGNE_PATH);

                  return csgn;
            }

            char str_pui[MAX_BUFFER_SIZE] = {0}; //Chaine pour consigne de puissance
            if(!fgets(str_pui, MAX_BUFFER_SIZE, sum_file_pointer)){ //Si la lecture rate
                  fprintf(stderr, "Failed to read on %s !", CONSIGNE_PATH);    
            }
            csgn = atof(str_pui);

            fclose(sum_file_pointer); // Suppression pointeur de fichier
            fclose(lock); // Suppression pointeur de fichier

            remove(LOCK_PATH); // On retire le verrou
      }
   
      return csgn;
}