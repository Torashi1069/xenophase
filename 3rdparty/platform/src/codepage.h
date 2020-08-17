#pragma once
#include <stddef.h> // size_t


/// Convert a string from one character encoding to another.
///
/// @param in_buf Input string
/// @param in_size Input string size, in bytes
/// @param in_cpname Input string codepage name
/// @param out_buf Output string buffer
/// @param out_size Output string buffer size, in bytes
/// @param out_cpname Output string codepage name
/// 
bool MultiByteToMultiByte(const char* in_buf, size_t in_size, const char* in_cpname, char* out_buf, size_t out_size, const char* out_cpname);
