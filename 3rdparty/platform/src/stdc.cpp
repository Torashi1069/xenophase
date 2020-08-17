#include "stdc.h"


#if defined(MSVC)
#include <string.h> // _stricmp(), _strnicmp()
int strcasecmp(const char* s1, const char* s2)
{
	return _stricmp(s1, s2);
}
int strncasecmp(const char* s1, const char* s2, size_t n)
{
	return _strnicmp(s1, s2, n);
}
#else
int stricmp(const char* s1, const char* s2)
{
	return strcasecmp(s1, s2);
}
int strnicmp(const char* s1, const char* s2, size_t n)
{
	return strncasecmp(s1, s2, n);
}
#endif


#if defined(MSVC) && MSVC_VER < 1400
#include <string.h> // memchr()
/// Find the length of STRING, but scan at most MAXLEN characters.
/// If no '\0' terminator is found in that many characters, return MAXLEN.
size_t strnlen(const char* string, size_t maxlen)
{
	const char* end = memchr(string, '\0', maxlen);
	return end ? (size_t) (end - string) : maxlen;
}
#endif
