#pragma once
#undef _DEBUG

// Compatibility Layer
#include <platform/system.h>
#include <platform/stdc.h>
#include <platform/disk.h>
#include <platform/macro.h>
#include <platform/network.h>
#include <platform/process.h>

// Windows SDK
#include <dbghelp.h>
#include <mmsystem.h>
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>

// C Runtime
#include <time.h>

// C++ Runtime
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <utility>

// Third-party
#include <detours/detours.h>
#include <libhook/libhook.h>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h> 
}
