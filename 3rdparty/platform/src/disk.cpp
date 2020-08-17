#include "disk.h"


#if defined(MSVC)
#include <direct.h> // _mkdir()
int mkdir(const char* path, int mode)
{
	return _mkdir(path);
}
#endif


#if defined(MSVC)
#include <fcntl.h> // _chsize()
int ftruncate(int fd, unsigned int length)
{
    return _chsize(fd, length);
}
#endif
