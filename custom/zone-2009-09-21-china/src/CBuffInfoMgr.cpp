#include "CBuffInfoMgr.hpp"


CBuffInfoMgr::CBuffInfoMgr(void)
{
}


CBuffInfoMgr::~CBuffInfoMgr(void)
{
	this->CBuffInfoMgr::Reset();
}


hook_method<bool (CBuffInfoMgr::*)(void)> CBuffInfoMgr::_Create(SERVER, "CBuffInfoMgr::Create");
bool CBuffInfoMgr::Create(void)
{
	return (this->*_Create)();

	//TODO
}


hook_method<bool (CBuffInfoMgr::*)(void)> CBuffInfoMgr::_InitBuffScript(SERVER, "CBuffInfoMgr::InitBuffScript");
bool CBuffInfoMgr::InitBuffScript(void)
{
	return (this->*_InitBuffScript)();

	//TODO
}


hook_method<CBuffInfo* (CBuffInfoMgr::*)(const char* buffName)> CBuffInfoMgr::_GetBuffInfo(SERVER, "?GetBuffInfo@CBuffInfoMgr@@QAEPAVCBuffInfo@@PBD@Z");
CBuffInfo* CBuffInfoMgr::GetBuffInfo(const char* buffName)
{
	return (this->*_GetBuffInfo)(buffName);

	//TODO
}


hook_method<CBuffInfo* (CBuffInfoMgr::*)(int buffType)> CBuffInfoMgr::_GetBuffInfo2(SERVER, "?GetBuffInfo@CBuffInfoMgr@@QAEPAVCBuffInfo@@H@Z");
CBuffInfo* CBuffInfoMgr::GetBuffInfo(int buffType)
{
	return (this->*_GetBuffInfo2)(buffType);

	//TODO
}


/* hook_method<bool (CBuffInfoMgr::*)(int buffType)> CBuffInfoMgr::_IsSendPacket(SERVER, "CBuffInfoMgr::IsSendPacket");
bool CBuffInfoMgr::IsSendPacket(int buffType)
{
	return (this->*_IsSendPacket)(buffType);

	//TODO
} */


hook_method<bool (CBuffInfoMgr::*)(unsigned long aid, int eventType, int buffType)> CBuffInfoMgr::_RunBuffScript(SERVER, "CBuffInfoMgr::RunBuffScript");
bool CBuffInfoMgr::RunBuffScript(unsigned long aid, int eventType, int buffType)
{
	return (this->*_RunBuffScript)(aid, eventType, buffType);

	//TODO
}


hook_method<int (CBuffInfoMgr::*)(const char* buffName)> CBuffInfoMgr::_GetBuffType(SERVER, "CBuffInfoMgr::GetBuffType");
int CBuffInfoMgr::GetBuffType(const char* buffName)
{
	return (this->*_GetBuffType)(buffName);

	//TODO
}


hook_method<CBuffInfo* (CBuffInfoMgr::*)(int buffType, const char* buffName)> CBuffInfoMgr::_AddBuffInfo(SERVER, "CBuffInfoMgr::AddBuffInfo");
CBuffInfo* CBuffInfoMgr::AddBuffInfo(int buffType, const char* buffName)
{
	return (this->*_AddBuffInfo)(buffType, buffName);

	//TODO
}


hook_method<CBuffInfo* (CBuffInfoMgr::*)(int buffTYpe, const char* buffName)> CBuffInfoMgr::_AddBuffInfoWithScript(SERVER, "CBuffInfoMgr::AddBuffInfoWithScript");
CBuffInfo* CBuffInfoMgr::AddBuffInfoWithScript(int buffTYpe, const char* buffName)
{
	return (this->*_AddBuffInfoWithScript)(buffTYpe, buffName);

	//TODO
}


hook_method<void (CBuffInfoMgr::*)(void)> CBuffInfoMgr::_Reset(SERVER, "CBuffInfoMgr::Reset");
void CBuffInfoMgr::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}
