#include "releve.h"

temp_t releve(usb *in){
    temp_t temperature = {-1,-1};
    DWORD RxBytes = 6;
    DWORD BytesReceived;
    char RxBuffer[6];
    unsigned int i;
    unsigned short t_ext = 0, t_int = 0;

    in->status = FT_Read(in->handle, RxBuffer, RxBytes, &BytesReceived);
    if ((in->status == FT_OK) && (BytesReceived == RxBytes)) {// FT_Read OK

        
        for(i=0; i<RxBytes; i++){
            printf("DUMP:%x\t", RxBuffer[i]);
            switch(RxBuffer[i]>>4){
                case 0:
                    t_ext |= (RxBuffer[i]&0x0F)<<8;
                break;
                case 1:
                    t_ext |= (RxBuffer[i]&0x0F)<<4;
                break;
                case 2:
                    t_ext |= (RxBuffer[i]&0x0F);
                break;
                case 8:
                    t_int |= (RxBuffer[i]&0x0F)<<8;
                break;
                case 9:
                    t_int |= (RxBuffer[i]&0x0F)<<4;
                break;
                case 10:
                    t_int |= (RxBuffer[i]&0x0F);
                break;
                default:
                break;
            }
        }

        printf("\nSOText:%d\tSOTint:%d\n", t_ext, t_int);
        temperature.exterieure = (float)t_ext*0.04-39.64;
        temperature.interieure = (float)t_int*0.04-39.64;
    }else {
        fprintf(stderr, "FT_Read Error \n");
    }

    return temperature;
}