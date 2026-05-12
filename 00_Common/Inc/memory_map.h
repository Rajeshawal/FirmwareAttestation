#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include "std_types.h"

/*
STM32F103C8T6 has 64 KB flash starting at 0x08000000.

Educational layout:
Bootloader : 0x08000000 - 0x08003FFF : 16 KB
App1       : 0x08004000 - 0x08009FFF : 24 KB current trusted app
App2       : 0x0800A000 - 0x0800EFFF : 20 KB new update staging app
*/

#define FLASH_BASE_ADDR          0x08000000UL

#define BOOTLOADER_START_ADDR    0x08000000UL
#define BOOTLOADER_SIZE_BYTES    (16UL * 1024UL)

#define APP1_START_ADDR          0x08004000UL
#define APP1_SIZE_BYTES          (24UL * 1024UL)

#define APP2_START_ADDR          0x0800A000UL
#define APP2_SIZE_BYTES          (20UL * 1024UL)

#define FLASH_PAGE_SIZE          1024UL

/* Valid hexadecimal magic number */
#define APP_MAGIC                0xEC1F00DUL

#define RSA2048_SIGNATURE_SIZE   256UL
#define SHA256_HASH_SIZE         32UL

/*
In this educational design, metadata is placed at the beginning of each slot.
After metadata comes the real application vector table and binary.
*/
typedef struct {
    u32 magic;

    u32 version_major;
    u32 version_minor;
    u32 version_patch;

    u32 image_size;                      /* Application binary size only, not metadata size */

    u8 sha256[SHA256_HASH_SIZE];          /* SHA-256 of application binary */
    u8 signature[RSA2048_SIGNATURE_SIZE]; /* RSA-2048 signature over SHA-256 hash */

} app_metadata_t;

#define APP_VECTOR_OFFSET        ((u32)sizeof(app_metadata_t))

#endif