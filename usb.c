#include "usb.h"

void initUSB(usb *in){
    in->status = FT_Open(0, &in->handle);
    if(in->status != FT_OK) {
        fprintf(stderr, "Error : Failed to open USB\n");

        return;
    }
}

void finUSB(usb *in){
    FT_Close(in->handle);
    free(in);
}