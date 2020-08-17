#pragma once
#include "common.h"


#if defined(MSVC)
#include <winsock2.h>
#else //non-MSVC
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#define SOCKET_ERROR (-1)
#endif
