#include "../Inc/bootloader.h"
#include "../../04_MCAL/Inc/rcc_interface.h"
#include "../../04_MCAL/Inc/can_interface.h"
#include "../../04_MCAL/Inc/gpio_interface.h"

int main(void)
{
    RCC_Init();
    RCC_EnableAFIO();
    RCC_EnableGPIOA();
    RCC_EnableCAN1();

    GPIO_CAN1_PinsInit();
    CAN1_Init_500Kbps();

    BOOTLOADER_Run();

    while (1) {}
}
