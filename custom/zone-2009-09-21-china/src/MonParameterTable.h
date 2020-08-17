#pragma once
#include "std/map"
#include "std/string"


class CMonsterParameterTable
{
	/* this+ 0 */ public: //const CMonsterParameterTable::`vftable';
	/* this+ 4 */ protected: mystd::map<mystd::string,unsigned long> m_spriteName;
	/* this+16 */ protected: mystd::map<mystd::string,unsigned long> m_mobName;

	public: CMonsterParameterTable::CMonsterParameterTable(void);
	public: virtual CMonsterParameterTable::~CMonsterParameterTable(void);
	public: void CMonsterParameterTable::Clear(void);
	public: HOOKED void CMonsterParameterTable::SetTable(void);
	public: void CMonsterParameterTable::SaveToFileMobName(const char* fName);
	public: void CMonsterParameterTable::SaveToFileNpcSpr(const char* fName);

private:
	static hook_method<void (CMonsterParameterTable::*)(void)> CMonsterParameterTable::_SetTable;
	static hook_method<void (CMonsterParameterTable::*)(void)> CMonsterParameterTable::_Clear;
	static hook_method<void (CMonsterParameterTable::*)(const char* fName)> CMonsterParameterTable::_SaveToFileMobName;
	static hook_method<void (CMonsterParameterTable::*)(const char* fName)> CMonsterParameterTable::_SaveToFileNpcSpr;
};
