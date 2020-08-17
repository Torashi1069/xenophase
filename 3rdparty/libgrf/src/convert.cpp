#include "convert.h"
#include <platform/codepage.h> // MultiByteToMultiByte()


bool convert_uhc_to_utf8(const char* in_buf, size_t in_size, char* out_buf, size_t out_size)
{
	return MultiByteToMultiByte(in_buf, in_size, "uhc", out_buf, out_size, "utf-8");
}


bool convert_utf8_to_uhc(const char* in_buf, size_t in_size, char* out_buf, size_t out_size)
{
	return MultiByteToMultiByte(in_buf, in_size, "utf-8", out_buf, out_size, "uhc");
}
