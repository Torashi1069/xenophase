#pragma once
#include <platform/stdc.h> // size_t, uint8_t


/// One 64-bit block.
typedef struct BIT64 { uint8_t b[8]; } BIT64;


void des_decrypt_block(BIT64* block);
void des_decrypt(uint8_t* data, size_t size);
