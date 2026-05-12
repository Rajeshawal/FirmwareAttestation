#include "../../06_Service/Inc/sha256_service.h"

/*
Educational placeholder.

In real STM32 firmware, use a small SHA-256 implementation such as:
- mbedTLS SHA-256
- tinycrypt SHA-256
- your own compact SHA-256 implementation

This stub must be replaced before real verification.
*/
void SHA256_Calculate(const u8 *data, u32 len, u8 out_hash[32])
{
    (void)data;
    (void)len;

    for (int i = 0; i < 32; i++) {
        out_hash[i] = 0;
    }
}
