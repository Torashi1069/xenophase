#pragma once
#include <platform/stdc.h> // size_t, uint8_t
#include <platform/macro.h> // ALIGN()


#define DES_BLOCKSIZE 8
#define DES_ALIGN(size) ALIGN(size,DES_BLOCKSIZE)


void grf_decode_data(uint8_t* buf, size_t len, uint8_t entry_type, int entry_len);
uint8_t* grf_decode_filename(uint8_t* buf, int len);
bool grf_file_is_mixcrypt(const char* fname);
