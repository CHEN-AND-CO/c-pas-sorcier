#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "define.h"
#include "simulateur.h"
#include "regulation.h"
#include "visualisationT.h"
#include "visualisationC.h"
#include "consigne.h"

void integrationTest(int regul,temp_t tInit,int nIterations);

#endif /* INTEGRATION_H */