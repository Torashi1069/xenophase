#pragma once
#include "common.h"


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#if defined(MSVC)
#include <direct.h>
#include <io.h>
int mkdir(const char* path, int mode);
int ftruncate(int fd, unsigned int length);
#else //non-MSVC
#include <unistd.h>
#endif
