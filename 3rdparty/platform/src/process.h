#pragma once
#include "common.h"


#if defined(MSVC)
#include <process.h>
#define getpid _getpid
#else //non-MSVC
#include <unistd.h>
#endif
