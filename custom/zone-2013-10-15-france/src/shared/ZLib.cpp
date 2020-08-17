#include "shared/ZLib.h"
#include <zlib/zlib.h>


CZLib::CZLib()
{
}


CZLib::~CZLib()
{
}


int CZLib::Compress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned int sourceLen, int level)
{
	return compress2(dest, destLen, source, sourceLen, level);
}


int CZLib::Uncompress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen)
{
	return uncompress(dest, destLen, source, sourceLen);
}
