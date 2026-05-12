#include <stdint.h>

/*
Replace this placeholder with real DER public key bytes.

Steps:
1. openssl rsa -pubin -in ecu1_public.pem -outform DER -out ecu1_public.der
2. xxd -i ecu1_public.der > ecu1_public_key.c
3. copy generated array here
*/

const unsigned char ecu1_public_der[] = {
    0x00
};

const unsigned int ecu1_public_der_len = 1;