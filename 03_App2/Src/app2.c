#include "../Inc/app2.h"
#include "../../05_HAL/Inc/led_interface.h"
#include "../../07_RTOS/Inc/rtos_interface.h"

void APP2_Run(void)
{
    LED_Init();

    while (1) {
        LED_Toggle();
        RTOS_DelayMs(150);
    }
}
