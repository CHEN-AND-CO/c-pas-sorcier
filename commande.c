#include "commande.h"

void commande(usb* usb, float puis) {
    DWORD written = 0;
    unsigned char tx_buf = ((char)(puis/100*127))&~(1<<8);

    usb->status = FT_Write(usb->handle, &tx_buf, sizeof(&tx_buf), &written);

    if (usb->status == FT_OK) {
        printf("FT_Write: Successfully written %d bytes :\t(%x)\n", written, tx_buf);
    } else {
        perror("FT_Write: Unable to write.\n");
    }
}