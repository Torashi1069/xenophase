#include "CAttackPlusPowerInfo.hpp"


CAttackPlusPowerInfo::CAttackPlusPowerInfo(void)
{
}


CAttackPlusPowerInfo::~CAttackPlusPowerInfo(void)
{
}


hook_method<void (CAttackPlusPowerInfo::*)(const char* filename)> CAttackPlusPowerInfo::_Init(SERVER, "CAttackPlusPowerInfo::Init");
void CAttackPlusPowerInfo::Init(const char* filename)
{
	return (this->*_Init)(filename);

	//TODO
}


hook_method<void (CAttackPlusPowerInfo::*)(const char* filename, int verDate)> CAttackPlusPowerInfo::_LoadScript(SERVER, "CAttackPlusPowerInfo::LoadScript");
void CAttackPlusPowerInfo::LoadScript(const char* filename, int verDate)
{
	return (this->*_LoadScript)(filename, verDate);

	//TODO
}


hook_method<int (CAttackPlusPowerInfo::*)(int defState, int atkState)> CAttackPlusPowerInfo::_GetAttackPlusPowerByProperty(SERVER, "?GetAttackPlusPowerByProperty@CAttackPlusPowerInfo@@QAEHHH@Z");
int CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(int defState, int atkState)
{
	return (this->*_GetAttackPlusPowerByProperty)(defState, atkState);

	//TODO
}


hook_method<void (CAttackPlusPowerInfo::*)(int defState, int atkState, int& result)> CAttackPlusPowerInfo::_GetAttackPlusPowerByProperty2(SERVER, "?GetAttackPlusPowerByProperty@CAttackPlusPowerInfo@@QAEXHHAAH@Z");
void CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(int defState, int atkState, int& result)
{
	return (this->*_GetAttackPlusPowerByProperty2)(defState, atkState, result);

	//TODO
}


/* hook_method<int (CAttackPlusPowerInfo::*)(int defState, int atkState, int in_damage)> CAttackPlusPowerInfo::_GetAttackPlusPowerByProperty_Variation(SERVER, "CAttackPlusPowerInfo::GetAttackPlusPowerByProperty_Variation");
int CAttackPlusPowerInfo::GetAttackPlusPowerByProperty_Variation(int defState, int atkState, int in_damage)
{
	return (this->*_GetAttackPlusPowerByProperty_Variation)(defState, atkState, in_damage);

	//TODO
} */


hook_method<int (CAttackPlusPowerInfo::*)(char* name)> CAttackPlusPowerInfo::_GetpropertyID(SERVER, "CAttackPlusPowerInfo::GetpropertyID");
int CAttackPlusPowerInfo::GetpropertyID(char* name)
{
	return (this->*_GetpropertyID)(name);

	//TODO
}


hook_method<void (CAttackPlusPowerInfo::*)(void)> CAttackPlusPowerInfo::_Reset(SERVER, "CAttackPlusPowerInfo::Reset");
void CAttackPlusPowerInfo::Reset(void)
{
	return (this->*_Reset)();

	m_propertyName.clear();
}
