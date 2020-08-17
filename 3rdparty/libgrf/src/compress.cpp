#include "compress.h"
#include <zlib.h>


uint32_t zlib_buffer_inflate(void* dest, uint32_t destlen, const void* src, uint32_t srclen)
{
	uLongf result = destlen;
	if( uncompress((Bytef*)dest, &result, (Bytef*)src, srclen) != Z_OK )
		return 0;
	return result;
}


uint32_t zlib_buffer_deflate(void* dest, uint32_t destlen, const void* src, uint32_t srclen)
{
	uLongf result = destlen;
	if( compress2((Bytef*)dest, &result, (Bytef*)src, srclen, Z_BEST_COMPRESSION) != Z_OK )
		return 0;
	return result;
}


uint32_t zlib_compressbound(uint32_t srclen)
{
	return compressBound(srclen);
}


uint32_t zlib_adler32(const void* buf, uint32_t size)
{
	uLong adler = adler32(0, NULL, 0); // = 1L;
	return adler32(adler, (const Bytef*)buf, size);
}
