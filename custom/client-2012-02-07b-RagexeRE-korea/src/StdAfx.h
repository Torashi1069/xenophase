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
#include <algorithm>
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
#include <zlib/zlib.h>


#undef _HAS_ITERATOR_DEBUGGING
#define _HAS_ITERATOR_DEBUGGING 0
#undef _SECURE_SCL
#define _SECURE_SCL 0
#undef _DEBUG


#include "std/std.hpp"
#include "std/algorithm"
#include "std/deque"
#include "std/hash_map"
#include "std/list"
#include "std/map"
#include "std/queue"
#include "std/set"
#include "std/stack"
#include "std/string"
#include "std/utility"
#include "std/vector"
