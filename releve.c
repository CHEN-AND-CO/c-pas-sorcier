#include "releve.h"

temp_t releve(usb *in){
    temp_t temperature = {0,0};
    DWORD RxBytes = 6;
    DWORD BytesReceived;
    char RxBuffer[MAX_BUFFER_SIZE];

    in->status = FT_Read(in->handle, RxBuffer, RxBytes, &BytesReceived);
    if (in->status == FT_OK) {
        if (BytesReceived == RxBytes) {// FT_Read OK

        }else {
            fprintf(stderr, "FT_Read Timeout \n");
        }
    }else {
        fprintf(stderr, "FT_Read Error \n");
    }

    return temperature;
}