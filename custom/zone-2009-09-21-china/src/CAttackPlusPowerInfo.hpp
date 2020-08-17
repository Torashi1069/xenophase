#pragma once
#include "std/map"
#include "std/string"
#include "struct.hpp"


class CAttackPlusPowerInfo
{
public:
	struct vtable_t // const CAttackPlusPowerInfo::`vftable'
	{
		 void* (CAttackPlusPowerInfo::* scalar_deleting_destructor)(unsigned int);
	};

	/* this+0x0   */ //const CAttackPlusPowerInfo::`vftable'
	/* this+0x4   */ AttrAttackInfo m_info[5];
	/* this+0x7D4 */ mystd::map<mystd::string,int> m_propertyName;

	public: CAttackPlusPowerInfo::CAttackPlusPowerInfo(void);
	public: virtual CAttackPlusPowerInfo::~CAttackPlusPowerInfo(void);
	public: void CAttackPlusPowerInfo::Init(const char* filename);
	public: void CAttackPlusPowerInfo::LoadScript(const char* filename, int verDate);
	public: int CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(int defState, int atkState);
	public: void CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(int defState, int atkState, int& result);
	public: int CAttackPlusPowerInfo::GetAttackPlusPowerByProperty_Variation(int defState, int atkState, int in_damage);
	public: int CAttackPlusPowerInfo::GetpropertyID(char* name);
	public: void CAttackPlusPowerInfo::Reset(void);

private:
	static hook_method<void (CAttackPlusPowerInfo::*)(const char* filename)> CAttackPlusPowerInfo::_Init;
	static hook_method<void (CAttackPlusPowerInfo::*)(const char* filename, int verDate)> CAttackPlusPowerInfo::_LoadScript;
	static hook_method<int (CAttackPlusPowerInfo::*)(int defState, int atkState)> CAttackPlusPowerInfo::_GetAttackPlusPowerByProperty;
	static hook_method<void (CAttackPlusPowerInfo::*)(int defState, int atkState, int& result)> CAttackPlusPowerInfo::_GetAttackPlusPowerByProperty2;
	static hook_method<int (CAttackPlusPowerInfo::*)(int defState, int atkState, int in_damage)> CAttackPlusPowerInfo::_GetAttackPlusPowerByProperty_Variation;
	static hook_method<int (CAttackPlusPowerInfo::*)(char* name)> CAttackPlusPowerInfo::_GetpropertyID;
	static hook_method<void (CAttackPlusPowerInfo::*)(void)> CAttackPlusPowerInfo::_Reset;
};
