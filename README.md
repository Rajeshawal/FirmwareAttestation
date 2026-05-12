# STM32F103C8T6 ECU Secure firmware over CAN

This is a cleaned educational project for firmware update over CAN.

## Hardware

- STM32F103C8T6 as ECU1
- MCP2551 CAN transceiver
- Primary ECU sends update to ECU1 through CAN

## Memory Layout

```text
0x08000000 ─ Bootloader, 16 KB
0x08004000 ─ App1, 24 KB, current trusted application
0x0800A000 ─ App2, 20 KB, new update staging application
```

## Main Idea

```text
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
```

## Cryptographic Demonstration GUIs

This project also includes educational Python Tkinter GUI tools to demonstrate firmware signing and verification logic used in secure boot and secure OTA/FOTA systems.

These GUIs help visualize:

- RSA key generation
- SHA-256 hashing
- firmware signing
- firmware verification
- public/private key usage
- secure firmware trust chain

They are intended for:

- embedded security learning
- firmware security demonstrations
- research presentations
- educational cryptographic workflow understanding

---

## Included GUI Tools

### 1. Key Generation GUI

```text
keygen_gui.py
```

Purpose:

- generate RSA private/public key pairs
- simulate OEM signing infrastructure
- export public key for ECU bootloader usage

Generated Files:

```text
private_key.pem
public_key.pem
public_key.der
```

Educational Flow:

```text
OEM Backend
    ↓
Generate RSA Key Pair
    ↓
Private Key → used for firmware signing
Public Key  → embedded into ECU bootloader
```

---

### 2. Firmware Signing GUI

```text
sign_gui.py
```

Purpose:

- select firmware binary
- calculate SHA-256 hash
- sign firmware hash using RSA private key
- generate signature file and metadata

Generated Files:

```text
firmware.bin
firmware.sig
metadata.bin
```

Educational Flow:

```text
Firmware Binary
    ↓
SHA-256 Hash
    ↓
RSA Private Key Signing
    ↓
Signed Firmware Package
```

---

### 3. Firmware Verification GUI

```text
verify_gui.py
```

Purpose:

- load firmware binary
- calculate SHA-256 hash
- verify RSA signature using public key
- demonstrate secure boot verification process

Educational Flow:

```text
Bootloader
    ↓
Load Public Key
    ↓
Calculate Firmware Hash
    ↓
Verify RSA Signature
    ↓
Accept or Reject Firmware
```

---

## Demonstrated Secure Firmware Architecture

```text
OEM / Primary ECU
    ↓
Generate firmware
    ↓
Sign firmware with private key
    ↓
Transmit firmware through CAN
    ↓
ECU Bootloader receives App2
    ↓
Bootloader verifies SHA-256 hash
    ↓
Bootloader verifies RSA signature using embedded public key
    ↓
If valid:
    copy App2 → App1
Else:
    reject update
```

## Important Educational Limitation

The following files still need real production implementation before hardware use:

- `04_MCAL/Src/can_program.c`
- `06_Service/Src/sha256_service.c`
- `06_Service/Src/crypto_service.c`

They are intentionally small so you can understand where real CAN, SHA-256, and RSA verification fit.

Read:

```text
09_Docs/REAL_IMPLEMENTATION_GUIDE.md
```

## Folder Summary

- `00_Common` shared types and memory map
- `01_Bootloader` bootloader decision logic
- `02_App1` current application
- `03_App2` new application source example
- `04_MCAL` low-level MCU drivers
- `05_HAL` board-level drivers
- `06_Service` update, version, hash, and crypto services
- `07_RTOS` simple delay placeholder
- `08_Linkers` memory linker examples
- `09_Docs` detailed explanation
- `10_PrimaryECU_Uploader_Simulation` CAN update protocol notes
- `11_GUI_Tools` educational cryptographic GUI demonstrations


# Educational Use Disclaimer

This project is intended strictly for:

- educational purposes
- research demonstrations
- embedded systems learning
- secure firmware update experimentation
- cybersecurity training
- academic demonstrations

This repository is NOT production-ready.

Several components intentionally contain simplified or placeholder implementations,
including:

- CAN communication handling
- SHA-256 implementation
- RSA signature verification
- bootloader hardening
- rollback protection
- fault tolerance
- secure key storage

The cryptographic verification flow is demonstrated conceptually to help learners
understand secure boot and FOTA architecture.

Placeholder functions that return fixed success values MUST NOT be used in real:
- automotive systems
- industrial control systems (ICS)
- operational technology (OT)
- medical devices
- aerospace systems
- safety-critical environments
- production embedded products

Before deployment on real hardware, production-grade implementations should be added using properly audited libraries such as:

- mbedTLS
- wolfSSL
- hardware secure elements
- secure boot protections
- authenticated update mechanisms

The authors assume no responsibility for misuse, damage, firmware corruption,
security failures, or unsafe deployment resulting from this educational code.

Use at your own risk.