--------------------------------------------------------------
 Platform Compatibility Layer
--------------------------------------------------------------


1. Overview
-----------

PCL addresses some basic differences between the C library in GCC and MSVC.
It handles all the #ifdefing, so you don't have to, making your code cleaner.


2. Usage
--------

Set the include path to the parent dir and use the headers you need:
#include <platform/stdc.h>    // stddef, stdio, stdlib, stdint, stdarg, string...
#include <platform/system.h>  // main system headers, for platform-specific projects
#include <platform/macro.h>   // useful macros (C_ASSERT, countof)
#include <platform/disk.h>    // files and directories
#include <platform/network.h> // sockets
#include <platform/process.h> // processes and threads
#include <platform/codepage.h>// codepage conversion
