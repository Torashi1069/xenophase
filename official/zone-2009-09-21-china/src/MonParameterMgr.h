#pragma once
#include "MonParameterTable.h"
#include "ODBC.h"
#include "std/map"
#include "struct.hpp"


class CMonParameterMgr : public CODBC, public CMonsterParameterTable
{
	/* this+ 0 */ public: //CODBC baseclass_0;
	/* this+20 */ public: //CMonsterParameterTable baseclass_14;
	/* this+48 */ private: mystd::map<unsigned long,MONPARAMETER*> m_parameter;
	/* this+60 */ private: mystd::map<unsigned long,MONSPAWN_SETINFO> m_spawnSetData;

	public: CMonParameterMgr::CMonParameterMgr(void);
	public: virtual CMonParameterMgr::~CMonParameterMgr(void);
	//public: int CMonParameterMgr::GetJob(const char*);
	public: void CMonParameterMgr::Init(const char* Script);
	public: unsigned long CMonParameterMgr::SearchKeyword(const char* keyword);
	public: MONPARAMETER* CMonParameterMgr::GetMonParameter(unsigned long spriteType);
	public: MONSPAWN_SETINFO* CMonParameterMgr::GetMonSpawnInfo(unsigned long spriteType);
	public: const char* CMonParameterMgr::GetMonsterName(unsigned long spriteType);
	public: int CMonParameterMgr::GetMonsterType(unsigned long spriteType);
	public: bool CMonParameterMgr::SetMonsterNameAndAIType(unsigned long spriteType, const char* name, int aiType);
	//private: void CMonParameterMgr::Load(const char*, const char*);
	private: void CMonParameterMgr::LoadSpawnInfo(void);
	//private: void CMonParameterMgr::InsertMonParameter(char*, MONPARAMETER*);
	private: void CMonParameterMgr::LoadMonParameter(void);
	private: void CMonParameterMgr::LoadMonMakingItem(void);
	private: void CMonParameterMgr::AddMonParameter(unsigned long spriteType, MONPARAMETER* parameter);
	private: void CMonParameterMgr::Destroy(void);
	private: void CMonParameterMgr::LoadEventMonParameter(void);
	private: void CMonParameterMgr::LoadEventMonMakingItem(void);

private:
	static hook_method<void (CMonParameterMgr::*)(const char* Script)> CMonParameterMgr::_Init;
	static hook_method<unsigned long (CMonParameterMgr::*)(const char* keyword)> CMonParameterMgr::_SearchKeyword;
	static hook_method<MONPARAMETER* (CMonParameterMgr::*)(unsigned long spriteType)> CMonParameterMgr::_GetMonParameter;
	static hook_method<MONSPAWN_SETINFO* (CMonParameterMgr::*)(unsigned long spriteType)> CMonParameterMgr::_GetMonSpawnInfo;
	static hook_method<const char* (CMonParameterMgr::*)(unsigned long spriteType)> CMonParameterMgr::_GetMonsterName;
	static hook_method<int (CMonParameterMgr::*)(unsigned long spriteType)> CMonParameterMgr::_GetMonsterType;
	static hook_method<bool (CMonParameterMgr::*)(unsigned long spriteType, const char* name, int aiType)> CMonParameterMgr::_SetMonsterNameAndAIType;
	static hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadSpawnInfo;
	static hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadMonParameter;
	static hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadMonMakingItem;
	static hook_method<void (CMonParameterMgr::*)(unsigned long spriteType, MONPARAMETER* parameter)> CMonParameterMgr::_AddMonParameter;
	static hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_Destroy;
	static hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadEventMonParameter;
	static hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadEventMonMakingItem;
};
