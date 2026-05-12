#ifndef FLASH_INTERFACE_H
#define FLASH_INTERFACE_H

#include "std_types.h"

void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_ErasePages(u32 start_addr, u32 size_bytes);
void FLASH_Write(u32 address, const u8 *data, u32 length);
void FLASH_Copy(u32 dst_addr, u32 src_addr, u32 length);

#endif
