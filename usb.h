#ifndef USB_H
#define USB_H

#ifdef __linux__
#include "ftd2xx.h"
//#include "WinTypes.h"
#else /* Lets assume its Windows */
#include "ftd2xx_windaube.h"
#endif

void initUSB();
void finUSB();

#endif /* USB_H */