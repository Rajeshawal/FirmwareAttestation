# STM32F103C8T6 ECU Secure firmware over CAN 

This is a cleaned educational project for firmware update over CAN.
## Hardware - STM32F103C8T6 as ECU1 - MCP2551 CAN transceiver - Primary ECU sends update to ECU1 through CAN 

## Memory Layout
text
0x08000000 ─ Bootloader, 16 KB
0x08004000 ─ App1, 24 KB, current trusted application
0x0800A000 ─ App2, 20 KB, new update staging application
## Main Idea
text
Power ON
↓
Bootloader runs first
↓
Primary ECU may upload new firmware + metadata into App2
↓
Bootloader compares App1 version and App2 version
↓
If App2 is newer:
    verify App2 hash and RSA signature
    if valid: copy App2 to App1
    if invalid: keep App1
↓
Bootloader jumps to App1
## Important Educational Limitation The following files still need real production implementation before hardware use: - 04_MCAL/Src/can_program.c - 06_Service/Src/sha256_service.c - 06_Service/Src/crypto_service.c They are intentionally small so you can understand where real CAN, SHA-256, and RSA verification fit. Read:
text
09_Docs/REAL_IMPLEMENTATION_GUIDE.md
## Folder Summary - 00_Common shared types and memory map - 01_Bootloader bootloader decision logic - 02_App1 current application - 03_App2 new application source example - 04_MCAL low-level MCU drivers - 05_HAL board-level drivers - 06_Service update, version, hash, and crypto services - 07_RTOS simple delay placeholder - 08_Linkers memory linker examples - 09_Docs detailed explanation - 10_PrimaryECU_Uploader_Simulation CAN update protocol notes
