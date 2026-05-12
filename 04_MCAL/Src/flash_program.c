#include "../../04_MCAL/Inc/flash_interface.h"
#include "../../00_Common/Inc/memory_map.h"
#include <stdint.h>

#define FLASH_REG_BASE  0x40022000UL
#define FLASH_KEYR      (*(volatile uint32_t *)(FLASH_REG_BASE + 0x04))
#define FLASH_SR        (*(volatile uint32_t *)(FLASH_REG_BASE + 0x0C))
#define FLASH_CR        (*(volatile uint32_t *)(FLASH_REG_BASE + 0x10))
#define FLASH_AR        (*(volatile uint32_t *)(FLASH_REG_BASE + 0x14))

#define FLASH_KEY1      0x45670123UL
#define FLASH_KEY2      0xCDEF89ABUL

static void flash_wait(void)
{
    while (FLASH_SR & 1U) {}
}

void FLASH_Unlock(void)
{
    FLASH_KEYR = FLASH_KEY1;
    FLASH_KEYR = FLASH_KEY2;
}

void FLASH_Lock(void)
{
    FLASH_CR |= (1U << 7);
}

void FLASH_ErasePages(u32 start_addr, u32 size_bytes)
{
    u32 end = start_addr + size_bytes;

    for (u32 addr = start_addr; addr < end; addr += FLASH_PAGE_SIZE) {
        flash_wait();
        FLASH_CR |= (1U << 1);   /* PER */
        FLASH_AR = addr;
        FLASH_CR |= (1U << 6);   /* STRT */
        flash_wait();
        FLASH_CR &= ~(1U << 1);
    }
}

void FLASH_Write(u32 address, const u8 *data, u32 length)
{
    FLASH_CR |= (1U << 0); /* PG */

    for (u32 i = 0; i < length; i += 2) {
        uint16_t halfword = data[i];
        if ((i + 1) < length) {
            halfword |= ((uint16_t)data[i + 1] << 8);
        }

        flash_wait();
        *(volatile uint16_t *)(address + i) = halfword;
        flash_wait();
    }

    FLASH_CR &= ~(1U << 0);
}

void FLASH_Copy(u32 dst_addr, u32 src_addr, u32 length)
{
    const u8 *src = (const u8 *)src_addr;
    FLASH_ErasePages(dst_addr, length);
    FLASH_Write(dst_addr, src, length);
}
