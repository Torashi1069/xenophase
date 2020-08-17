#include "CCharMTInfo.hpp"


CCharMTInfo::CCharMTInfo(void)
{
	m_attackedMTInfo = 0;
}


CCharMTInfo::~CCharMTInfo(void)
{
}


hook_method<void (CCharMTInfo::*)(void)> CCharMTInfo::_Init(SERVER, "CCharMTInfo::Init");
void CCharMTInfo::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CCharMTInfo::*)(void)> CCharMTInfo::_LoadAttackMTInfo(SERVER, "CCharMTInfo::LoadAttackMTInfo");
void CCharMTInfo::LoadAttackMTInfo(void)
{
	return (this->*_LoadAttackMTInfo)();

	//TODO
}


/* hook_method<void (CCharMTInfo::*)(void)> CCharMTInfo::_LoadAttackedMTInfo(SERVER, "CCharMTInfo::LoadAttackedMTInfo");
void CCharMTInfo::LoadAttackedMTInfo(void)
{
	return (this->*_LoadAttackedMTInfo)();

	//TODO
} */


hook_method<int (CCharMTInfo::*)(unsigned long job, unsigned long itemType)> CCharMTInfo::_GetAttackMT(SERVER, "CCharMTInfo::GetAttackMT");
int CCharMTInfo::GetAttackMT(unsigned long job, unsigned long itemType)
{
	return (this->*_GetAttackMT)(job, itemType);

	//TODO
}


/* hook_method<int (CCharMTInfo::*)(unsigned long job)> CCharMTInfo::_GetAttackedMT(SERVER, "CCharMTInfo::GetAttackedMT");
int CCharMTInfo::GetAttackedMT(unsigned long job)
{
	return (this->*_GetAttackedMT)(job);

	//TODO
} */
