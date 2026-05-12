#include "../../04_MCAL/Inc/gpio_interface.h"
#include <stdint.h>

#define GPIOA_BASE   0x40010800UL
#define GPIOB_BASE   0x40010C00UL
#define GPIOA_CRL    (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_CRH    (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR    (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))

void GPIOA_PinOutput(u8 pin)
{
    if (pin < 8) {
        GPIOA_CRL &= ~(0xFUL << (pin * 4));
        GPIOA_CRL |=  (0x2UL << (pin * 4)); /* Output push-pull, 2 MHz */
    } else {
        u8 p = pin - 8;
        GPIOA_CRH &= ~(0xFUL << (p * 4));
        GPIOA_CRH |=  (0x2UL << (p * 4));
    }
}

void GPIOA_PinToggle(u8 pin)
{
    GPIOA_ODR ^= (1UL << pin);
}

void GPIO_CAN1_PinsInit(void)
{
    /* STM32F103 CAN1 default:
       PA11 = CAN RX input
       PA12 = CAN TX alternate function push-pull
       MCP2551 connects between CAN TX/RX and CANH/CANL.
       This is simplified educational config. */
}
