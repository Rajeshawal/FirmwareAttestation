#include "../../05_HAL/Inc/led_interface.h"
#include "../../04_MCAL/Inc/gpio_interface.h"
#include "../../04_MCAL/Inc/rcc_interface.h"

#define LED_PIN 5

void LED_Init(void)
{
    RCC_EnableGPIOA();
    GPIOA_PinOutput(LED_PIN);
}

void LED_Toggle(void)
{
    GPIOA_PinToggle(LED_PIN);
}
