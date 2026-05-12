#ifndef SHA256_SERVICE_H
#define SHA256_SERVICE_H

#include "std_types.h"

void SHA256_Calculate(const u8 *data, u32 len, u8 out_hash[32]);

#endif
