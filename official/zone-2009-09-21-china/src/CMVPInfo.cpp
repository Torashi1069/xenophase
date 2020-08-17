#include "CMVPInfo.hpp"


hook_method<void (CMVPInfo::*)(void)> CMVPInfo::_Reset(SERVER, "CMVPInfo::Reset");
void CMVPInfo::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<void (CMVPInfo::*)(void)> CMVPInfo::_LoadInfoFromDB(SERVER, "CMVPInfo::LoadInfoFromDB");
void CMVPInfo::LoadInfoFromDB(void)
{
	return (this->*_LoadInfoFromDB)();

	//TODO
}


hook_method<MVPINFO* (CMVPInfo::*)(unsigned long job)> CMVPInfo::_GetInfo(SERVER, "CMVPInfo::GetInfo");
MVPINFO* CMVPInfo::GetInfo(unsigned long job)
{
	return (this->*_GetInfo)(job);

	//TODO
}


hook_method<void (CMVPInfo::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, char type)> CMVPInfo::_Init(SERVER, "CMVPInfo::Init");
void CMVPInfo::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, char type)
{
	return (this->*_Init)(DSN, UID, PASS, DB, type);

	//TODO
}


hook_method<void (CMVPInfo::*)(unsigned long job, MVPINFO* info)> CMVPInfo::_AddInfo(SERVER, "CMVPInfo::AddInfo");
void CMVPInfo::AddInfo(unsigned long job, MVPINFO* info)
{
	return (this->*_AddInfo)(job, info);

	//TODO
}
