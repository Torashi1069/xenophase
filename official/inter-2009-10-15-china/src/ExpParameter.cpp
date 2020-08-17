#include "ExpParameter.h"


hook_method<void (CExpParameter::*)(const char* script, const char* dbPassword)> CExpParameter::_Init(SERVER, "CExpParameter::Init");
void CExpParameter::Init(const char* script, const char* dbPassword)
{
	return (this->*_Init)(script, dbPassword);

	//TODO
}
