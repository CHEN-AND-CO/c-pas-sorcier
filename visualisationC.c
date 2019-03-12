#include "visualisationC.h"

void visualisationC(float puissance_f)
{
   if(access(DATA_LOCK_PATH, F_OK) != -1){ // Vérifie si le fichier est disponible      
         fprintf(stderr, "File %s doesn\'t exist !", DATA_PATH);
   } else {
         FILE *lock = fopen(DATA_LOCK_PATH, "w"); // Crée le verrou d'accès
         FILE *sum_file_pointer = NULL;

         if (access(DATA_PATH, F_OK) == -1) {
            sum_file_pointer = fopen(DATA_PATH, "w+"); // Crée le fichier de consigne
         } else {
            sum_file_pointer = fopen(DATA_PATH, "r+"); // Ouvre le fichier de consigne
         }

         if(!sum_file_pointer){ // Vérifie si on a réussi à ouvrir le fichier
            fprintf(stderr, "Failed to open %s !", DATA_PATH);
            return;
         }

         char *str_pui = malloc(MAX_BUFFER_SIZE*sizeof(char *)); //Chaine pour consigne de puissance
         if(puissance_f > 0){
            str_pui = "true\n";
         }else{
            str_pui = "false\n";
         }

         char tmp[MAX_BUFFER_SIZE] = {0};
         rewind(sum_file_pointer);
         fgets(tmp, MAX_BUFFER_SIZE, sum_file_pointer);
         fgets(tmp, MAX_BUFFER_SIZE, sum_file_pointer);
         
         if(fputs(str_pui, sum_file_pointer)==-1){ //Si l'écriture rate
            fprintf(stderr, "Failed to write on %s !", DATA_PATH);    
         }

         fclose(sum_file_pointer); // Suppression pointeur de fichier
         fclose(lock); // Suppression pointeur de fichier

         remove(DATA_LOCK_PATH); // On retire le verrou
   }
}
