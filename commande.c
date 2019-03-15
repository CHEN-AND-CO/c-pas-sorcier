#include "commande.h"

void commande(usb *usb, float puis) {
  DWORD written = 0; // Bytes written
  unsigned char tx_buf = ((char)(puis / 100 * 127)) & ~(1 << 8); // Data to send

  usb->status =
      FT_Write(usb->handle, &tx_buf, sizeof(&tx_buf), &written); // USB Write

  if (usb->status == FT_OK) { // Write success
    #ifdef __linux__
    printf("FT_Write: Successfully written %d bytes :\t(%x)\n", written,
           tx_buf);
    #else
    printf("FT_Write: Successfully written %ld bytes :\t(%x)\n", written,
           tx_buf);
    #endif
  } else {
    perror("FT_Write: Unable to write.\n"); // Failure
  }
}