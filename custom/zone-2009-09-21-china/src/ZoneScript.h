#pragma once
#include "CAttackPlusPowerInfo.hpp"
#include "std/list"
#include "std/map"
#include "std/string"
#include "std/vector"
#include "enum.hpp"
#include "struct.hpp"


class CZoneScript
{
public:
	/* this+  0 */ private: mystd::map<unsigned short,mystd::vector<extraITMInfo> > m_makingArrowInfo;
	/* this+ 12 */ private: mystd::map<unsigned short,mystd::vector<extraITMInfo> > m_makeElemental;
	/* this+ 24 */ private: mystd::map<unsigned short,mystd::vector<extraITMInfo> > m_makeCook[10];
	/* this+144 */ private: mystd::list<mystd::string> m_idTable[20];
	/* this+384 */ private: mystd::list<unsigned long> m_aidTable;
	/* this+396 */ private: CAttackPlusPowerInfo* m_attackPlusPowerInfo;
	/* this+400 */ private: mystd::map<unsigned long,SummonMobList> m_metamorphosisInfo;
	/* this+412 */ private: mystd::map<unsigned long,SummonMobList> m_summonSlaveInfo;
	/* this+424 */ private: mystd::map<unsigned long,int> m_mobEmotionInfo;
	/* this+436 */ private: mystd::map<short,mystd::map<unsigned short,short> > m_abracadabraInfo;
	/* this+448 */ private: mystd::map<mystd::string,int> m_itmGroupName;
	/* this+460 */ private: mystd::map<int,mystd::vector<extraITMInfo> > m_itmGroupInfo;
	/* this+472 */ private: STAT_PLUSTABLE m_statPlus_LvUp[4];

	public: CZoneScript::CZoneScript(void);
	public: CZoneScript::~CZoneScript(void);
	public: void CZoneScript::Init(void);
	public: void CZoneScript::Reset(void);
	//public: mystd::map<unsigned short,mystd::vector<extraITMInfo> > CZoneScript::GetMakingArrowItemInfo();
	//public: mystd::map<unsigned short,mystd::vector<extraITMInfo> > CZoneScript::GetMakingElementalInfo();
	//public: mystd::map<unsigned short,mystd::vector<extraITMInfo> > CZoneScript::GetMakingCookInfo(short);
	public: int CZoneScript::SearchID(char* id, enum MYCHECK_TYPE func);
	public: void CZoneScript::GetAtkPlusPWByProperty(int defState, int atkState, int& result);
	public: int CZoneScript::GetAtkPlusPWByProperty(int defState, int atkState);
	//public: int CZoneScript::GetAtkPlusPWByProperty_Variation(int, int, int);
	public: void CZoneScript::LoadMetamorphosisInfo(void);
	//public: SummonMobList* CZoneScript::GetMetamorphosis(unsigned long);
	public: void CZoneScript::LoadSummonSlaveInfo(void);
	//public: SummonMobList* CZoneScript::GetSummonSlaveList(unsigned long);
	//public: void CZoneScript::LoadSummonMobInfo(const char *, mystd::map<unsigned long,SummonMobList> &);
	public: void CZoneScript::LoadMobEmotionInfo(void);
	//public: int CZoneScript::GetMobEmotion(unsigned long);
	public: void CZoneScript::LoadAbracadabraInfo(void);
	//public: unsigned short CZoneScript::GetSkillByAbracadabra(short);
	public: unsigned long CZoneScript::GetITMFromGroupID(int groupID);
	//public: unsigned long CZoneScript::GetCatchAID();
	//public: unsigned long CZoneScript::GetRemoveCatchAID();
	//public: int CZoneScript::CheckAID(unsigned long);
	//public: STAT_PLUSTABLE* CZoneScript::GetStatPlusTBL(short);
	private: int CZoneScript::LoadMakingArrowInfo(void);
	private: int CZoneScript::Load_MK_ElementalInfo(void);
	private: int CZoneScript::Load_MK_CookInfo(void);
	private: int CZoneScript::LoadItemGroupInfo(const char* fileName);
	private: int CZoneScript::LoadHomunInfo(const char* fName);
	private: int CZoneScript::CheckAvaibleID(char* id, enum MYCHECK_TYPE func);
	private: void CZoneScript::LoadIDTable(void);
	private: void CZoneScript::ClearIDTable(void);
	private: void CZoneScript::LoadAIDTable(void);
	private: int CZoneScript::GetITMGroupID(char* itmName);
	//private: int CZoneScript::GetField(lua_State*, const char *);

private:
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_Init;
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_Reset;
	static hook_method<int (CZoneScript::*)(char* id, enum MYCHECK_TYPE func)> CZoneScript::_SearchID;
	static hook_method<void (CZoneScript::*)(int defState, int atkState, int& result)> CZoneScript::_GetAtkPlusPWByProperty;
	static hook_method<int (CZoneScript::*)(int defState, int atkState)> CZoneScript::_GetAtkPlusPWByProperty2;
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadMetamorphosisInfo;
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadSummonSlaveInfo;
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadMobEmotionInfo;
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadAbracadabraInfo;
	static hook_method<unsigned long (CZoneScript::*)(int groupID)> CZoneScript::_GetITMFromGroupID;
	static hook_method<int (CZoneScript::*)(void)> CZoneScript::_LoadMakingArrowInfo;
	static hook_method<int (CZoneScript::*)(void)> CZoneScript::_Load_MK_ElementalInfo;
	static hook_method<int (CZoneScript::*)(void)> CZoneScript::_Load_MK_CookInfo;
	static hook_method<int (CZoneScript::*)(const char* fileName)> CZoneScript::_LoadItemGroupInfo;
	static hook_method<int (CZoneScript::*)(const char* fName)> CZoneScript::_LoadHomunInfo;
	static hook_method<int (CZoneScript::*)(char* id, enum MYCHECK_TYPE func)> CZoneScript::_CheckAvaibleID;
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadIDTable;
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_ClearIDTable;
	static hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadAIDTable;
	static hook_method<int (CZoneScript::*)(char* itmName)> CZoneScript::_GetITMGroupID;
};


class CMatchTable
{
	struct vtable_t
	{
		int (CMatchTable::* StringToKey)(char* keyString); //__purecall
		int (CMatchTable::* StringToDest)(char* destString); //__purecall
	};

	/* this+0 */ public: //const CMatchTable::`vftable';
	/* this+4 */ protected: mystd::map<int,mystd::vector<int>*> m_matchMap;

	enum { NOMATCH = -1 };

	public: CMatchTable::CMatchTable(void);
	public: CMatchTable::~CMatchTable(void);
	public: void CMatchTable::LoadFromFile(const char* fileName);
	public: int CMatchTable::GetRandomMatch(int n);
	public: virtual int CMatchTable::StringToKey(char* keyString) = 0;
	public: virtual int CMatchTable::StringToDest(char* destString) = 0;

private:
	static hook_method<void (CMatchTable::*)(const char* fileName)> CMatchTable::_LoadFromFile;
	static hook_method<int (CMatchTable::*)(int n)> CMatchTable::_GetRandomMatch;
};


class CSummonItemTable : public CMatchTable
{
	struct vtable_t
	{
		int (CSummonItemTable::* StringToKey)(char* keyString);
		int (CSummonItemTable::* StringToDest)(char* destString);
	};

	/* this+0 */ public: //CMatchTable baseclass_0;

	public: virtual int CSummonItemTable::StringToKey(char* keyString);
	public: virtual int CSummonItemTable::StringToDest(char* destString);

private:
	static hook_method<int (CSummonItemTable::*)(char* keyString)> CSummonItemTable::_StringToKey;
	static hook_method<int (CSummonItemTable::*)(char* destString)> CSummonItemTable::_StringToDest;
};


extern CSummonItemTable& g_summonItemTable;


class CSummonMobBySkillTable : public CMatchTable
{
	struct vtable_t
	{
		int (CSummonMobBySkillTable::* StringToKey)(char* keyString);
		int (CSummonMobBySkillTable::* StringToDest)(char* destString);
	};

	/* this+0 */ public: //CMatchTable baseclass_0;

	public: virtual int CSummonMobBySkillTable::StringToKey(char* keyString);
	public: virtual int CSummonMobBySkillTable::StringToDest(char* destString);

private:
	static hook_method<int (CSummonMobBySkillTable::*)(char* keyString)> CSummonMobBySkillTable::_StringToKey;
	static hook_method<int (CSummonMobBySkillTable::*)(char* destString)> CSummonMobBySkillTable::_StringToDest;
};


extern CSummonMobBySkillTable& g_summonMobBySkillTable;
