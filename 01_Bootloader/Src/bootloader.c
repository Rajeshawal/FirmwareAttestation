#include "../Inc/bootloader.h"
#include "../../00_Common/Inc/memory_map.h"
#include "../../06_Service/Inc/version_service.h"
#include "../../06_Service/Inc/crypto_service.h"
#include "../../04_MCAL/Inc/flash_interface.h"
#include "../../06_Service/Inc/update_service.h"
#include <stdint.h>

typedef void (*app_entry_t)(void);

static const app_metadata_t *app1_meta = (const app_metadata_t *)APP1_START_ADDR;
static const app_metadata_t *app2_meta = (const app_metadata_t *)APP2_START_ADDR;

static bool_t metadata_is_valid(const app_metadata_t *meta)
{
    if (meta->magic != APP_MAGIC) {
        return FALSE;
    }

    if (meta->image_size == 0) {
        return FALSE;
    }

    return TRUE;
}

void BOOTLOADER_Run(void)
{
    /*
    Optional update receive step:
    The Primary ECU may send a new firmware image and metadata through CAN.
    This function stores that update in App2.
    */
    UPDATE_ReceiveFromCAN();

    /*
    App1 is the current trusted application.
    App2 is the new update slot.
    */
    if (metadata_is_valid(app1_meta) && metadata_is_valid(app2_meta)) {

        if (VERSION_Compare(app1_meta, app2_meta) < 0) {

            if (CRYPTO_VerifyAppImage(APP2_START_ADDR) == TRUE) {

                u32 total_size = APP_VECTOR_OFFSET + app2_meta->image_size;

                if (total_size <= APP1_SIZE_BYTES) {
                    FLASH_Unlock();
                    FLASH_Copy(APP1_START_ADDR, APP2_START_ADDR, total_size);
                    FLASH_Lock();
                }
            }
        }
    }

    BOOTLOADER_JumpToApp1();
}

void BOOTLOADER_JumpToApp1(void)
{
    /*
    App1 layout:
    APP1_START_ADDR
        ├── app_metadata_t
        └── vector table
              ├── initial MSP
              └── reset handler
    */

    u32 app_vector = APP1_START_ADDR + APP_VECTOR_OFFSET;

    u32 app_stack = *(volatile u32 *)(app_vector + 0);
    u32 app_reset = *(volatile u32 *)(app_vector + 4);

    __asm volatile ("msr msp, %0" : : "r" (app_stack) : );

    app_entry_t app = (app_entry_t)app_reset;
    app();
}
