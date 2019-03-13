#ifndef USB_H
#define USB_H

#include "ftd2xx.h"


#ifdef _WIN32
#endif /* _WIN32 */

#ifdef linux
#endif /* linux */



void initUSB();
void finUSB();

#endif /* USB_H */