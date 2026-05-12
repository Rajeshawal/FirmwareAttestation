#include "../Inc/app1.h"
#include "../../05_HAL/Inc/led_interface.h"
#include "../../07_RTOS/Inc/rtos_interface.h"

void APP1_Run(void)
{
    LED_Init();

    while (1) {
        LED_Toggle();
        RTOS_DelayMs(500);
    }
}
