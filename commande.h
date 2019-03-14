#ifndef COMMANDE_H
#define COMMANDE_H

#include "define.h"
#include "usb.h"

/* Send the power command through USB */
void commande(usb *usb, float puis);

#endif /* COMMANDE_H */