# 05_HAL

HAL means Hardware Abstraction Layer.

This layer controls board-level devices using MCAL.

## Files

### `led_interface.h` / `led_program.c`

Simple LED driver.

It uses GPIO from MCAL.

## Difference Between MCAL and HAL

MCAL knows MCU pins and registers.  
HAL knows external or board-level devices, such as LEDs, buttons, relays, or sensors.
