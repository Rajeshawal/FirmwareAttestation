# STM32F103C8T6 ECU1 Memory Map

STM32F103C8T6 flash size: 64 KB  
Flash base: `0x08000000`

Educational partition layout:

| Region | Start Address | Size | Purpose |
|---|---:|---:|---|
| Bootloader | `0x08000000` | 16 KB | Runs first, verifies App2, copies App2 to App1, jumps to App1 |
| App1 | `0x08004000` | 24 KB | Current trusted application |
| App2 | `0x0800A000` | 20 KB | New update received from Primary ECU through CAN |
| Metadata | inside App1/App2 headers | small | Version, hash, signature info |

Real production bootloaders usually reserve dedicated pages for flags, metadata, rollback state, counters, and cryptographic key storage.
