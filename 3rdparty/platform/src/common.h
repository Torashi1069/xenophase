#pragma once


// WINDOWS
#if !defined(WINDOWS) && (defined(_WINDOWS) || defined(WIN32) || defined(_WIN32))
#define WINDOWS
#endif


// MSVC
#if !defined(MSVC) && defined(_MSC_VER)
#define MSVC
#define MSVC_VER _MSC_VER
// 2005 | 2008 | 2010 | 2012
// -----+------+------+-----
// 1400 | 1500 | 1600 | 1700
#endif


// warnings
#if defined(MSVC)
#pragma warning(disable: 4065) //warning C4065: switch statement contains 'default' but no 'case' labels
#pragma warning(disable: 4200) //warning C4200: nonstandard extension used : zero-sized array in struct/union. Cannot generate copy-ctor or copy-assignment operator when UDT contains a zero-sized array.
#pragma warning(disable: 4996) //warning C4996: '%s': This function or variable may be unsafe. Consider using %s_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
#endif
