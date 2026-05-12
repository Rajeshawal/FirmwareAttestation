# 00_Common

This folder contains files shared by bootloader, App1, App2, and services.

## Files

### `Inc/std_types.h`

Defines simple fixed-width types:

- `u8`
- `u16`
- `u32`
- `bool_t`

### `Inc/memory_map.h`

Defines the flash partition addresses:

- Bootloader start and size
- App1 start and size
- App2 start and size
- metadata structure

## Why This Folder Exists

All modules must agree on the same flash layout.  
If App1, App2, and bootloader use different addresses, the bootloader may copy or jump to the wrong location.
