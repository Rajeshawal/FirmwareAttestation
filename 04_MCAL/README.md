# 04_MCAL

MCAL means Microcontroller Abstraction Layer.

This layer talks directly to STM32F103C8T6 hardware registers or STM32 HAL drivers.

## Files

### `rcc_interface.h` / `rcc_program.c`

Clock control.

### `gpio_interface.h` / `gpio_program.c`

GPIO pin control.

### `can_interface.h` / `can_program.c`

CAN driver interface.

Current file is an educational placeholder.  
Replace with STM32 HAL CAN or direct bxCAN driver.

### `flash_interface.h` / `flash_program.c`

Flash erase, write, and copy functions.

## Why MCAL Exists

Higher layers should not directly access MCU registers.  
They should call MCAL functions instead.
