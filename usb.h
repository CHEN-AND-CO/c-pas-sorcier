#ifndef USB_H
#define USB_H

#include <stdlib.h>
#include <stdio.h>

#ifdef __linux__
#include "ftd2xx.h"
//#include "WinTypes.h"
#elif _WIN32
#include "ftd2xx_windaube.h"
#endif

typedef struct
{
    FT_STATUS status;
    FT_HANDLE handle;
} usb;

void initUSB(usb *in);

void finUSB(usb *in);

#endif /* USB_H */