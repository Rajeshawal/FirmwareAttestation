#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include "std_types.h"

typedef struct {
    u32 id;
    u8  dlc;
    u8  data[8];
} can_frame_t;

void CAN1_Init_500Kbps(void);
bool_t CAN1_Receive(can_frame_t *frame);
void CAN1_Send(const can_frame_t *frame);

#endif
