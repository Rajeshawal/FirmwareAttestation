# 01_Bootloader

The bootloader is the first code that runs after reset.

## Files

### `Inc/bootloader.h`

Declares:

- `BOOTLOADER_Run()`
- `BOOTLOADER_JumpToApp1()`

### `Src/main.c`

Initializes basic hardware and calls the bootloader.

### `Src/bootloader.c`

Main bootloader logic:

1. Receive update from CAN into App2.
2. Compare App1 and App2 versions.
3. If App2 is newer, verify App2.
4. If verification passes, copy App2 to App1.
5. Jump to App1.

### `Src/ecu1_public_key.c`

Placeholder public key file.

In real implementation, replace with DER public key bytes generated from your RSA public key.

## Important

The bootloader should stay protected.  
If the bootloader is corrupted, the ECU may not boot.
