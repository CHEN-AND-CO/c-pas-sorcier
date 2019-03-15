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

/* Open an USB Connexion */
void initUSB(usb *in);

/* Close and delete the USB connexion */
void finUSB(usb *in);

#endif /* USB_H */