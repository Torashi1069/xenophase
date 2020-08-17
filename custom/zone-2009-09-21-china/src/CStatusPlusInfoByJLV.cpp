#include "CStatusPlusInfoByJLV.hpp"


CStatusPlusInfoByJLV::CStatusPlusInfoByJLV(void)
{
}


CStatusPlusInfoByJLV::~CStatusPlusInfoByJLV(void)
{
}


hook_method<void (CStatusPlusInfoByJLV::*)(void)> CStatusPlusInfoByJLV::_Init(SERVER, "CStatusPlusInfoByJLV::Init");
void CStatusPlusInfoByJLV::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<STATUS* (CStatusPlusInfoByJLV::*)(unsigned long job, unsigned char level)> CStatusPlusInfoByJLV::_GetResultPlusStatusInfo(SERVER, "CStatusPlusInfoByJLV::GetResultPlusStatusInfo");
STATUS* CStatusPlusInfoByJLV::GetResultPlusStatusInfo(unsigned long job, unsigned char level)
{
	return (this->*_GetResultPlusStatusInfo)(job, level);

	//TODO
}
