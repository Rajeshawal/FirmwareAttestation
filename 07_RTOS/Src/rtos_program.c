#include "../../07_RTOS/Inc/rtos_interface.h"

/*
Educational RTOS placeholder.
Replace with FreeRTOS if needed.
*/

void RTOS_Start(void)
{
}

void RTOS_DelayMs(unsigned int ms)
{
    volatile unsigned int count;
    while (ms--) {
        count = 8000;
        while (count--) {}
    }
}
