# Primary ECU to ECU1 CAN Update Protocol

Physical:
Primary ECU CAN TX/RX -> MCP2551 -> CANH/CANL -> MCP2551 -> ECU1 STM32F103 CAN RX/TX

CAN IDs:
- `0x100` START_UPDATE
- `0x101` METADATA_CHUNK
- `0x102` FIRMWARE_CHUNK
- `0x103` END_UPDATE

Bootloader behavior:
1. Receive App2 metadata + binary through CAN.
2. Store update into App2 flash region.
3. On next boot, compare App1 and App2 versions.
4. If App2 version is newer, verify App2 hash and RSA signature.
5. If verification succeeds, copy App2 into App1.
6. Jump to App1.
7. If verification fails, keep App1 and jump to App1.
