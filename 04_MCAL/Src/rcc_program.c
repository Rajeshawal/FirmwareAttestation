#include "../../04_MCAL/Inc/rcc_interface.h"
#include <stdint.h>

#define RCC_BASE        0x40021000UL
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x1C))

void RCC_Init(void)
{
    /* Minimal educational placeholder.
       In production, configure HSE/PLL/system clock carefully. */
}

void RCC_EnableGPIOA(void) { RCC_APB2ENR |= (1U << 2); }
void RCC_EnableGPIOB(void) { RCC_APB2ENR |= (1U << 3); }
void RCC_EnableAFIO(void)  { RCC_APB2ENR |= (1U << 0); }
void RCC_EnableCAN1(void)  { RCC_APB1ENR |= (1U << 25); }
