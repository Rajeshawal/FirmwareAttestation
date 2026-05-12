#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "std_types.h"

#define GPIO_OUTPUT_2MHZ  0x2
#define GPIO_OUTPUT_10MHZ 0x1
#define GPIO_OUTPUT_50MHZ 0x3

void GPIOA_PinOutput(u8 pin);
void GPIOA_PinToggle(u8 pin);
void GPIO_CAN1_PinsInit(void);

#endif
