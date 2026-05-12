# 03_App2

App2 is the update staging slot.

## Purpose

The Primary ECU sends the new firmware to ECU1.  
ECU1 stores that new firmware in App2 first.

App2 is not trusted immediately.  
The bootloader verifies App2 before copying it to App1.

## Files

### `Inc/app2.h`

Declares the App2 run function.

### `Src/app2.c`

Simple example application.  
It blinks an LED faster than App1 so you can visually see that an update happened.

### `Src/main.c`

Application entry point.

## Update Flow

```text
Primary ECU
↓ CAN
ECU1 bootloader
↓
write new firmware to App2
↓
verify App2
↓
copy App2 to App1
```
