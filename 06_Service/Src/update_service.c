#include "../Inc/update_service.h"
#include "../../04_MCAL/Inc/can_interface.h"
#include "../../04_MCAL/Inc/flash_interface.h"
#include "../../00_Common/Inc/memory_map.h"

/*
Primary ECU sends update to ECU1 through CAN.

CAN IDs:
0x100 = START_UPDATE
0x101 = DATA_CHUNK
0x103 = END_UPDATE

Data layout written into App2:
APP2_START_ADDR
    ├── app_metadata_t
    └── new application binary
*/

#define CAN_ID_START_UPDATE     0x100
#define CAN_ID_DATA_CHUNK       0x101
#define CAN_ID_END_UPDATE       0x103

void UPDATE_ReceiveFromCAN(void)
{
    can_frame_t frame;
    u32 write_addr = APP2_START_ADDR;

    while (CAN1_Receive(&frame)) {

        if (frame.id == CAN_ID_START_UPDATE) {
            FLASH_Unlock();
            FLASH_ErasePages(APP2_START_ADDR, APP2_SIZE_BYTES);
            write_addr = APP2_START_ADDR;
        }

        else if (frame.id == CAN_ID_DATA_CHUNK) {

            if ((write_addr + frame.dlc) <= (APP2_START_ADDR + APP2_SIZE_BYTES)) {
                FLASH_Write(write_addr, frame.data, frame.dlc);
                write_addr += frame.dlc;
            }
        }

        else if (frame.id == CAN_ID_END_UPDATE) {
            FLASH_Lock();
            break;
        }
    }
}
