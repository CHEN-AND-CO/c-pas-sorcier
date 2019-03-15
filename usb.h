#ifndef USB_H
#define USB_H

#include <stdlib.h>
#include <stdio.h>

#include "ftd2xx.h"

typedef struct
{
    FT_STATUS status;
    FT_HANDLE handle;
} usb;

void initUSB(usb *in);

void finUSB(usb *in);

#endif /* USB_H */