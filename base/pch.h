#pragma once

// Compatibility Layer
#include <platform/system.h>
#include <platform/stdc.h>
#include <platform/disk.h>
#include <platform/macro.h>
#include <platform/network.h>
#include <platform/process.h>

// Windows SDK
#include <mmsystem.h>

// C Runtime
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <process.h>
#include <io.h>
#include <sys/stat.h>

// C++ Runtime
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <typeinfo> //RTTI
#include <utility> //pair<>
#include <vector>

// Third-party
#include <detours/detours.h>
#include <libhook/libhook.h>

// Local
#include "test.hpp"
#define SERVER EXEPATH()
#define SAKEXE EXEPATH()

#undef small // conflict with SDK\RpcNdr.h
#undef _HAS_ITERATOR_DEBUGGING
#define _HAS_ITERATOR_DEBUGGING 0
#undef _SECURE_SCL
#define _SECURE_SCL 0
#undef _DEBUG

// vc2010
#if defined(_MSC_VER) && _MSC_VER == 1600
#ifdef _Fpz
#undef _Fpz
#endif
#ifndef _DESTRUCTOR
#define _DESTRUCTOR(ty, ptr)   (ptr)->~ty()
#endif
#ifndef _PROTECTED
#define _PROTECTED     protected
#endif
#ifndef _SCL_SECURE_TRAITS_VALIDATE
#define _SCL_SECURE_TRAITS_VALIDATE(cond)
#endif
#ifndef _SCL_SECURE_TRAITS_VALIDATE_RANGE
#define _SCL_SECURE_TRAITS_VALIDATE_RANGE(cond)
#endif
#endif /* defined(_MSC_VER) && _MSC_VER == 1600 */

#include "std/std.hpp"
#include "std/algorithm"
#include "std/deque"
#include "std/hash_map"
#include "std/list"
#include "std/map"
#include "std/queue"
#include "std/set"
#include "std/stack"
#include "std/stdio"
#include "std/string"
#include "std/utility"
#include "std/vector"
