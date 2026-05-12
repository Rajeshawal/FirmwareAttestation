# 06_Service

This layer contains reusable system services.

## Files

### `version_service.h` / `version_service.c`

Compares App1 and App2 versions.

### `sha256_service.h` / `sha256_service.c`

Calculates SHA-256 hash.

Current implementation is a placeholder.  
Replace with mbedTLS or wolfSSL.

### `crypto_service.h` / `crypto_service.c`

Verifies:

1. App2 hash
2. App2 RSA-SHA256 signature

Current RSA function is a placeholder.  
Replace with mbedTLS or wolfSSL.

### `update_service.h` / `update_service.c`

Receives update data from Primary ECU over CAN and writes it into App2.

## Why Service Layer Exists

The bootloader should remain simple.  
Complex tasks like update receiving, hashing, signature checking, and version comparison are placed here.
