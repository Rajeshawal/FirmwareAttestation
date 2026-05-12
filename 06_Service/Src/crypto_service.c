#include "../Inc/crypto_service.h"
#include "../Inc/sha256_service.h"
#include "../../00_Common/Inc/memory_map.h"

extern const unsigned char ecu1_public_der[];
extern const unsigned int ecu1_public_der_len;

/*
This file shows the correct verification flow.

The RSA function below is still a placeholder because real RSA needs
mbedTLS or wolfSSL. See 09_Docs/REAL_IMPLEMENTATION_GUIDE.md.
*/

bool_t CRYPTO_RSA_Verify_SHA256(const u8 hash[32], const u8 signature[256])
{
    (void)ecu1_public_der;
    (void)ecu1_public_der_len;
    (void)hash;
    (void)signature;

    /*
    Replace this with real mbedTLS RSA-SHA256 verification.

    Important:
    Returning TRUE is only for learning the bootloader flow.
    Do not use this placeholder on real hardware.
    */
    return TRUE;
}

bool_t CRYPTO_VerifyAppImage(u32 slot_start_addr)
{
    const app_metadata_t *meta = (const app_metadata_t *)slot_start_addr;
    const u8 *image = (const u8 *)(slot_start_addr + APP_VECTOR_OFFSET);
    u8 calculated_hash[SHA256_HASH_SIZE];

    if (meta->magic != APP_MAGIC) {
        return FALSE;
    }

    if (meta->image_size == 0) {
        return FALSE;
    }

    SHA256_Calculate(image, meta->image_size, calculated_hash);

    for (u32 i = 0; i < SHA256_HASH_SIZE; i++) {
        if (calculated_hash[i] != meta->sha256[i]) {
            return FALSE;
        }
    }

    return CRYPTO_RSA_Verify_SHA256(meta->sha256, meta->signature);
}
