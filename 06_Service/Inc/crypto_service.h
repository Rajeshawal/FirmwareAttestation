#ifndef CRYPTO_SERVICE_H
#define CRYPTO_SERVICE_H

#include "../../00_Common/Inc/std_types.h"

bool_t CRYPTO_VerifyAppImage(u32 slot_start_addr);
bool_t CRYPTO_RSA_Verify_SHA256(const u8 hash[32], const u8 signature[256]);

#endif
