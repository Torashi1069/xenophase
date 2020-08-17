#pragma once
#include "common.h"


/// std headers
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>


/// basic types
#include <sys/types.h>
//
#if defined(MSVC)
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif
//
#if defined(MSVC)
typedef INT8  int8_t;
typedef INT16 int16_t;
typedef INT32 int32_t;
typedef INT64 int64_t;
typedef UINT8  uint8_t;
typedef UINT16 uint16_t;
typedef UINT32 uint32_t;
typedef UINT64 uint64_t;
typedef INT_PTR intptr_t;
typedef UINT_PTR uintptr_t;
#else //non-MSVC
#include <stdint.h>
#endif


/// strings
#include <string.h>
#include <stdio.h>
//
#if defined(MSVC)
#define snprintf _snprintf
#endif
//
#if defined(MSVC)
int strcasecmp(const char* s1, const char* s2);
int strncasecmp(const char* s1, const char* s2, size_t n);
#else
int stricmp(const char* s1, const char* s2);
int strnicmp(const char* s1, const char* s2, size_t n);
#endif
//
#if defined(MSVC) && MSVC_VER < 1400
size_t strnlen(const char* string, size_t maxlen);
#endif
