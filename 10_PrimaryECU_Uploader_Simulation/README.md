# 10_PrimaryECU_Uploader_Simulation

This folder explains the Primary ECU update protocol.

## Purpose

The Primary ECU sends firmware and metadata to ECU1 through CAN.

## CAN IDs

```text
0x100 = START_UPDATE
0x101 = DATA_CHUNK
0x103 = END_UPDATE
```

## Data Written to App2

```text
APP2_START_ADDR
├── app_metadata_t
└── firmware binary
```

## Future Work

You can add a Python sender using:

- python-can
- USB-CAN adapter
- CANable
- PCAN
- SocketCAN
