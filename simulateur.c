#include "unistd.h"
#include "simulateur.h"


#define CTH  73746.9
#define RGF_A 0.00686
#define RGF_B 0.01003
#define RGF_C 0.01155
#define PUISS_MAX 3200
#define DELTA_T 10.0
/*******************************/
/* Construction des parametres	*/
/**********************************/
   struct simParam_s* simConstruct(temp_t temperature){
     /* Variables */
      struct simParam_s* param_ps;
      int i=0;
   
      /* Allocation mémoire*/
      param_ps = malloc(sizeof(struct simParam_s));
   
      /*initialisation de chaque champ*/
      param_ps->tempInt_f = temperature.interieure;
      param_ps->tempExt_f = temperature.exterieure;
      param_ps->rgf = RGF_A;
      param_ps->kr = (CTH*param_ps->rgf)/DELTA_T;
      param_ps->trace_pf = fopen("trace.txt","w");
      param_ps->compteur_i = 0;
      
      /* intialisation fichier trace*/
      if( param_ps->trace_pf == NULL){
         perror("Erreur dans simConstruct() : impossible d'ouvrir le fichier trace.txt\n");
         exit(EXIT_FAILURE);
      }
      fprintf(param_ps->trace_pf,"%f \t %f \t %f \t %f\n",param_ps->compteur_i*DELTA_T,0.0,param_ps->tempExt_f,param_ps->tempInt_f);      
   	return param_ps;
   }

 temp_t simCalc(float puissance, struct simParam_s* param_ps){
     
      temp_t temperature;
      temperature.exterieure = param_ps->tempExt_f;

      if((puissance > 100)|| (puissance < 0)){
         /* puissance erronee */
         printf("Simulateur : erreur de puissance\n");
          temperature.interieure = param_ps->tempInt_f;

      }else{

         /* Simulateur	 */
         temperature.interieure = (param_ps->tempExt_f + param_ps->rgf*PUISS_MAX * ((float)puissance / 100.0) + ((float)param_ps->tempInt_f*param_ps->kr))/(param_ps->kr+1.0);
      }
   	/* Ecriture des donnees dans le fichier trace.txt */
      printf("Simulateur : P=%g%%, Temp ext.=%g deg, Temp int.=%g deg\n",puissance,param_ps->tempExt_f,param_ps->tempInt_f);
      
      param_ps->compteur_i++;
      fprintf(param_ps->trace_pf,"%f \t %f \t %f \t %f\n",param_ps->compteur_i*DELTA_T,puissance,param_ps->tempExt_f,param_ps->tempInt_f);


      /*sauvegarde de la temperature*/
      param_ps->tempInt_f = temperature.interieure;

      return temperature;
   }


   void simDestruct(struct simParam_s* param_ps){
      fclose(param_ps->trace_pf);
      free(param_ps);
   }
