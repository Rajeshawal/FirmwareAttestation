#include "../../04_MCAL/Inc/can_interface.h"

/*
Educational CAN stub.

For a real STM32CubeIDE project, replace this file with HAL CAN or direct bxCAN register code.
MCP2551 is only the physical CAN transceiver. STM32F103 internal bxCAN controller still sends/receives frames.

Expected update protocol from Primary ECU:
CAN ID 0x100: START_UPDATE
CAN ID 0x101: METADATA_CHUNK
CAN ID 0x102: FIRMWARE_CHUNK
CAN ID 0x103: END_UPDATE
*/

void CAN1_Init_500Kbps(void)
{
    /* Configure bxCAN at 500 kbps here. */
}

bool_t CAN1_Receive(can_frame_t *frame)
{
    (void)frame;
    return FALSE;
}

void CAN1_Send(const can_frame_t *frame)
{
    (void)frame;
}
