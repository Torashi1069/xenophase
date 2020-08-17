#pragma once
#include <platform/stdc.h> // size_t


bool convert_uhc_to_utf8(const char* in_buf, size_t in_size, char* out_buf, size_t out_size);
bool convert_utf8_to_uhc(const char* in_buf, size_t in_size, char* out_buf, size_t out_size);
