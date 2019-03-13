#include "releve.h"

temp_t releve(usb *in){
    temp_t temperature = {-1,-1}; // By default the temperatures will be -1 and -1
    DWORD RxBytes = 6; // 3 Bytes for t_ext and 3 others for t_int
    DWORD BytesReceived; //
    char RxBuffer[6];
    unsigned char tmp = 0;
    unsigned int i;
    unsigned short t_ext = 0, t_int = 0;

    in->status = FT_Read(in->handle, RxBuffer, RxBytes, &BytesReceived);
    if ((in->status == FT_OK) && (BytesReceived == RxBytes)) {// FT_Read OK
        for(i=0; i<RxBytes; i++){ // On parcours les >6 octets reçus
            printf("DUMP:%x\t", RxBuffer[i]);

            tmp = RxBuffer[i]&0xFF; //Pour une raison inconnue, certaines valeurs de RxBuffer sont +grandes que 8bits
            switch(tmp>>4){
                case 0: // Bits 11 à 8 de t_ext
                    t_ext |= (tmp&0x0F)<<8;
                break;
                case 1: // Bits 7 à 4 de t_ext
                    t_ext |= (tmp&0x0F)<<4;
                break;
                case 2: // Bits 3 à 1 de t_ext
                    t_ext |= (tmp&0x0F);
                break;
                case 8: // Bits 11 à 8 de t_int
                    t_int |= (tmp&0x0F)<<8;
                break;
                case 9: // Bits 7 à 4 de t_int
                    t_int |= (tmp&0x0F)<<4;
                break;
                case 10: // Bits 3 à 1 de t_int
                    t_int |= (tmp&0x0F);
                break;
                default:
                break;
            }
        }

        printf("FT_Read success, %dBytes read", BytesReceived); //Debug

        printf("\nSOText:%d\tSOTint:%d\n", t_ext, t_int); //Debug
        temperature.exterieure = (float)t_ext*0.04-39.64; //SOT_ext => t_ext
        temperature.interieure = (float)t_int*0.04-39.64; //SOT_int => t_int
    }else {
        fprintf(stderr, "FT_Read Error \n"); //Erreur de lecture 
    }

    return temperature;
}