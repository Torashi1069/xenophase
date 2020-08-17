#pragma once
#include "common.h"


/// Compile-time assertion.
#if !defined(C_ASSERT)
#if defined(MSVC)
#include <windows.h> //-> winnt.h
#else
#define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
#endif
#endif


/// Length of a fixed-size array (in fields).
#if !defined(countof)
#if defined(MSVC)
#define countof _countof
#else
template <typename T, size_t N> char (& __countof__(T (&X)[N] ))[N]; // T[N]& -> char[N]&
#define countof(X) ( sizeof(__countof__(X)) )
#endif
#endif // countof


/// Round value up to nearest multiple of 'n'.
#if !defined(ALIGN)
#define ALIGN(x,n) ( ((x) + (n) - 1) - ((x) + (n) - 1) % (n) )
#endif


/// Limit value to a certain range.
#if !defined(min)
#define min(a,b) ( ( (a) < (b) ) ? (a) : (b) )
#endif
#if !defined(max)
#define max(a,b) ( ( (a) > (b) ) ? (a) : (b) )
#endif
#if !defined(CAP_VALUE)
#define CAP_VALUE(val, min, max) ( ( (val) < (min) ) ? (min) : ( (val) > (max) ) ? (max) : (val) )
#endif
