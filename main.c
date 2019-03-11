#include "define.h"
#include "regulation.h"
int main(){
    float tab[5] = {10.0, 11.0, 12.0, 13.0, 14.0};
    float targ = 13;

    printf("%f\n", regulationTest(2, targ, tab, 5));

    return 0;
}