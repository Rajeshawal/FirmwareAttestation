# 02_App1

App1 is the current trusted application slot.

## Purpose

The bootloader jumps to App1 after checking whether App2 should replace it.

## Files

### `Inc/app1.h`

Declares the App1 run function.

### `Src/app1.c`

Simple example application.  
It blinks an LED slowly.

### `Src/main.c`

Application entry point.

## In Real Project

App1 would contain the real ECU application logic, such as:

- sensor reading
- actuator control
- CAN communication
- diagnostics
- control algorithms
