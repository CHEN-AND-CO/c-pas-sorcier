#include "integration.h"

void integrationTest(int regul,temp_t tInit,int nIterations){
    int tab_len = 1;
    float *tab_temp = malloc(tab_len*sizeof(float *));
    float powa = 0.0, csgn = 0.0;

    tab_temp[0] = tInit.interieure;

    csgn = consigne((float)0.0);
    powa = regulation(regul, csgn, tab_temp, tab_len);
    while(tab_len < nIterations){
        tab_temp = realloc(tab_temp, ++tab_len);
        tInit = temperatures(tInit);
        tab_temp[tab_len-1]=tInit.interieure;
        csgn = consigne(0.0);
        powa = regulation(regul, csgn, tab_temp, tab_len);
        visualisationC(powa);
    }
}
