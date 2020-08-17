#pragma once
#include "common.h"


#if defined(MSVC)
#define WIN32_LEAN_AND_MEAN
#define WIN32_NO_STATUS
#define _WINSOCKAPI_
#include <windows.h>
#undef WIN32_NO_STATUS
#undef _WINSOCKAPI_
#include <ntstatus.h>
#include <winternl.h>
#endif
