#include "commande.h"

void commande(float puis) {
  usb *in = malloc(sizeof(usb));
  initUSB(in);

  DWORD written = 0; // Bytes written
  unsigned char tx_buf[1] = {((char)(puis / 100 * 127)) & ~(1 << 8)}; // Data to send

  printf("Puissance : %d\n", tx_buf[0]);

  in->status =
      FT_Write(in->handle, tx_buf, sizeof(tx_buf), &written); // USB Write

  if (in->status == FT_OK) { // Write success
    #ifdef __linux__
    printf("FT_Write: Successfully written %d bytes :\t(%x)\n", written,
           tx_buf[0]);
    #else
    printf("FT_Write: Successfully written %ld bytes :\t(%x)\n", written,
           tx_buf[0]);
    #endif
  } else {
    perror("FT_Write: Unable to write.\n"); // Failure
  }

  finUSB(in);
}