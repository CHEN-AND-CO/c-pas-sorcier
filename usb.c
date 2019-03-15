#include "usb.h"

void initUSB(usb *in)
{
    in->status = FT_Open(0, &in->handle); // Open an USB Connexion
    if (in->status != FT_OK) // Failure
    {
        fprintf(stderr, "Error : Failed to open USB\n");

        return;
    }
}

void finUSB(usb *in)
{
    FT_Close(in->handle); // Close USB Connexion
    free(in); // Remove from memory
}