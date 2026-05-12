# Real Implementation Guide

This project is intentionally educational.  
The project structure and bootloader logic are useful, but three parts must be replaced before real hardware use:

1. CAN driver
2. SHA-256 hash function
3. RSA-SHA256 signature verification

---

## 1. CAN Driver

STM32F103C8T6 has an internal CAN controller called bxCAN.

MCP2551 is only the physical transceiver.

```text
STM32F103 bxCAN
    PA12 CAN_TX
    PA11 CAN_RX
        ↓
MCP2551
        ↓
CANH / CANL
```

### STM32CubeIDE Setup

Enable:

```text
Connectivity → CAN
```

Use:

```text
PA11 = CAN_RX
PA12 = CAN_TX
Normal Mode
500 kbps
```

### Replace Placeholder

Replace:

```text
04_MCAL/Src/can_program.c
```

with STM32 HAL CAN or direct bxCAN code.

---

## 2. MCP2551 Wiring

| STM32F103C8T6 | MCP2551 |
|---|---|
| PA12 CAN_TX | TXD |
| PA11 CAN_RX | RXD |
| GND | GND |
| 5V | VDD |

| MCP2551 | CAN Bus |
|---|---|
| CANH | CANH |
| CANL | CANL |

Use 120-ohm termination resistors at both ends of the CAN bus.

---

## 3. Real SHA-256 using mbedTLS

Replace:

```text
06_Service/Src/sha256_service.c
```

with real mbedTLS SHA-256.

Example:

```c
#include "sha256_service.h"
#include "mbedtls/sha256.h"

void SHA256_Calculate(const uint8_t *data,
                      uint32_t len,
                      uint8_t out_hash[32])
{
    mbedtls_sha256(data, len, out_hash, 0);
}
```

---

## 4. Real RSA-SHA256 Verification

Replace:

```text
06_Service/Src/crypto_service.c
```

with real mbedTLS RSA verification.

Example:

```c
#include "crypto_service.h"
#include "mbedtls/pk.h"

extern const unsigned char ecu1_public_der[];
extern const unsigned int ecu1_public_der_len;

bool_t CRYPTO_RSA_Verify_SHA256(
    const uint8_t hash[32],
    const uint8_t signature[256])
{
    mbedtls_pk_context pk;
    mbedtls_pk_init(&pk);

    int ret = mbedtls_pk_parse_public_key(
        &pk,
        ecu1_public_der,
        ecu1_public_der_len
    );

    if (ret != 0) {
        return FALSE;
    }

    ret = mbedtls_pk_verify(
        &pk,
        MBEDTLS_MD_SHA256,
        hash,
        32,
        signature,
        256
    );

    mbedtls_pk_free(&pk);

    return (ret == 0) ? TRUE : FALSE;
}
```

---

## 5. Public Key Integration

Convert public key from PEM to DER:

```bash
openssl rsa -pubin -in ecu1_public.pem -outform DER -out ecu1_public.der
```

Convert DER to C array:

```bash
xxd -i ecu1_public.der > ecu1_public_key.c
```

Then replace:

```text
01_Bootloader/Src/ecu1_public_key.c
```

---

## 6. Correct Bootloader Verification Flow

```text
Power ON
↓
Bootloader
↓
Receive possible CAN update into App2
↓
Read App1 metadata
↓
Read App2 metadata
↓
If App2 version <= App1 version:
    jump App1
↓
If App2 version > App1 version:
    calculate SHA-256 of App2 binary
    compare with App2 metadata hash
    verify RSA signature using public key
↓
If valid:
    erase App1
    copy App2 to App1
    jump App1
↓
If invalid:
    keep App1
    jump App1
```

---

## 7. Production Improvements

Add later:

- rollback protection
- update state flags
- power-loss recovery
- watchdog recovery
- boot success confirmation
- failed update rollback
- encrypted firmware
- hardware root of trust
- secure key storage
