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
#include <hash_map>
#include <queue>
#include <tuple>
#include <utility>

// Third-party
#include <detours/detours.h>
#include <libhook/libhook.h>

// Misc
#undef GetMessage // WinUser.h
#undef PostMessage // WinUser.h
#undef LogonUser // WinBase.h
