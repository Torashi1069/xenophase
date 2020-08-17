#include "ZLib.h"
#include "globals.hpp"


hook_method<void (CZLib::*)(void)> CZLib::_CZLib(SERVER, "CZLib::CZLib");
CZLib::CZLib(void)
{
}


hook_method<void (CZLib::*)(void)> CZLib::__CZLib(SERVER, "CZLib::~CZLib");
CZLib::~CZLib(void)
{
}


hook_method<int (CZLib::*)(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen, int level)> CZLib::_Compress(SERVER, "CZLib::Compress");
int CZLib::Compress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen, int level)
{
	return (this->*_Compress)(dest, destLen, source, sourceLen, level);

	return compress2(dest, destLen, source, sourceLen, level);
}


hook_method<int (CZLib::*)(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen)> CZLib::_Uncompress(SERVER, "CZLib::Uncompress");
int CZLib::Uncompress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen)
{
	return (this->*_Uncompress)(dest, destLen, source, sourceLen);

	return uncompress(dest, destLen, source, sourceLen);
}
