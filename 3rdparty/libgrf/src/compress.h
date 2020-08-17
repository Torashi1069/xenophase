#pragma once
#include <platform/stdc.h> // uint32_t


uint32_t zlib_buffer_inflate(void* dest, uint32_t destlen, const void* src, uint32_t srclen);
uint32_t zlib_buffer_deflate(void* dest, uint32_t destlen, const void* src, uint32_t srclen);
uint32_t zlib_compressbound(uint32_t srclen);
uint32_t zlib_adler32(const void* buf, uint32_t size);
