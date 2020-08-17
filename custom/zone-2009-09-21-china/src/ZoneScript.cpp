#include "CITPMgr.hpp"
#include "MonParameterMgr.h"
#include "CSkillTypeInfoMgr.hpp"
#include "Path.h"
#include "ZoneProcess.h"
#include "ZoneScript.h"
#include "globals.hpp"
#include "shared.h" // Trace()


CZoneScript::CZoneScript(void) // line 19
{
}


CZoneScript::~CZoneScript(void) // line 23
{
	this->CZoneScript::Reset();
}


hook_method<void (CZoneScript::*)(void)> CZoneScript::_Init(SERVER, "CZoneScript::Init");
void CZoneScript::Init(void) // line 29
{
	return (this->*_Init)();

	this->CZoneScript::LoadMakingArrowInfo();
	this->CZoneScript::Load_MK_ElementalInfo();
	this->CZoneScript::Load_MK_CookInfo();
	this->CZoneScript::LoadIDTable();

	m_attackPlusPowerInfo = new CAttackPlusPowerInfo();
	m_attackPlusPowerInfo->CAttackPlusPowerInfo::Init(g_pathData->CPathData::SetFileName("attsuccesspercentinfo.scp"));
	this->CZoneScript::LoadMetamorphosisInfo();
	this->CZoneScript::LoadSummonSlaveInfo();
	this->CZoneScript::LoadMobEmotionInfo();
	this->CZoneScript::LoadAbracadabraInfo();

	m_itmGroupName["ITMGROUP_ORE"] = 1;
	m_itmGroupName["ITMGROUP_GEM"] = 2;
	m_itmGroupName["ITMGROUP_HEAL"] = 3;
	m_itmGroupName["ITMGROUP_FOOD"] = 4;

	if( !this->CZoneScript::LoadItemGroupInfo(g_pathData->CPathData::SetFileName("ItemGroupList.txt")) )
		ExitProcess(EXIT_SUCCESS);

	if( !this->CZoneScript::LoadHomunInfo(g_pathData->CPathData::SetFileName("Homun.scp")) )
		ExitProcess(EXIT_SUCCESS);
}


hook_method<void (CZoneScript::*)(void)> CZoneScript::_Reset(SERVER, "CZoneScript::Reset");
void CZoneScript::Reset(void) // line 79
{
	return (this->*_Reset)();

	m_makingArrowInfo.clear();
	m_makeElemental.clear();

	for( int i = 0; i < countof(m_makeCook); ++i )
		m_makeCook[i].clear();

	this->CZoneScript::ClearIDTable();

	m_aidTable.clear();

	if( m_attackPlusPowerInfo != NULL )
	{
		m_attackPlusPowerInfo->CAttackPlusPowerInfo::Reset();
		delete m_attackPlusPowerInfo;
	}

	m_metamorphosisInfo.clear();
	m_summonSlaveInfo.clear();
	m_mobEmotionInfo.clear();
	m_abracadabraInfo.clear();

	memset(m_statPlus_LvUp, 0, sizeof(m_statPlus_LvUp));
}


hook_method<int (CZoneScript::*)(char* id, enum MYCHECK_TYPE func)> CZoneScript::_SearchID(SERVER, "CZoneScript::SearchID");
int CZoneScript::SearchID(char* id, enum MYCHECK_TYPE func) // line 479
{
	return (this->*_SearchID)(id, func);

	return ( id != NULL && func < CHECK_MAX_NUM ) ? this->CZoneScript::CheckAvaibleID(id, func) : 0;
}


//hook_method<void (CZoneScript::*)(int defState, int atkState, int& result)> CZoneScript::_GetAtkPlusPWByProperty(SERVER, "?GetAtkPlusPWByProperty@CZoneScript@@QAEXHHAAH@Z");
void CZoneScript::GetAtkPlusPWByProperty(int defState, int atkState, int& result) // line ???
{
//	return (this->*_GetAtkPlusPWByProperty)(defState, atkState, result);

	if( m_attackPlusPowerInfo != NULL )
		m_attackPlusPowerInfo->CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(defState, atkState, result);
	else
		result = 0;
}


//hook_method<int (CZoneScript::*)(int defState, int atkState)> CZoneScript::_GetAtkPlusPWByProperty2(SERVER, "?GetAtkPlusPWByProperty@CZoneScript@@QAEHHH@Z");
int CZoneScript::GetAtkPlusPWByProperty(int defState, int atkState) // line ???
{
//	return (this->*_GetAtkPlusPWByProperty2)(defState, atkState);

	int result;

	if( m_attackPlusPowerInfo != NULL )
		result = m_attackPlusPowerInfo->CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(defState, atkState);
	else
		result = 0;

	return result;
}


hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadMetamorphosisInfo(SERVER, "CZoneScript::LoadMetamorphosisInfo");
void CZoneScript::LoadMetamorphosisInfo(void) // line 900
{
	return (this->*_LoadMetamorphosisInfo)();

	//TODO
}


hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadSummonSlaveInfo(SERVER, "CZoneScript::LoadSummonSlaveInfo");
void CZoneScript::LoadSummonSlaveInfo(void) // line 918
{
	return (this->*_LoadSummonSlaveInfo)();

	//TODO
}


hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadMobEmotionInfo(SERVER, "CZoneScript::LoadMobEmotionInfo");
void CZoneScript::LoadMobEmotionInfo(void) // line 987
{
	return (this->*_LoadMobEmotionInfo)();

	//TODO
}


hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadAbracadabraInfo(SERVER, "CZoneScript::LoadAbracadabraInfo");
void CZoneScript::LoadAbracadabraInfo(void) // line 1031
{
	return (this->*_LoadAbracadabraInfo)();

	//TODO
}


hook_method<unsigned long (CZoneScript::*)(int groupID)> CZoneScript::_GetITMFromGroupID(SERVER, "CZoneScript::GetITMFromGroupID");
unsigned long CZoneScript::GetITMFromGroupID(int groupID) // line 624
{
	return (this->*_GetITMFromGroupID)(groupID);

	mystd::map<int,mystd::vector<extraITMInfo> >::const_iterator iter = m_itmGroupInfo.find(groupID);
	if( iter == m_itmGroupInfo.end() )
		return 0;

	const extraITMInfo* entry = &iter->second[GetServerRandom(0, 20000) % iter->second.size()];
	if( GetServerRandom(0, 20000) % 10000 >= entry->num )
		return 0;

	return entry->id;
}


hook_method<int (CZoneScript::*)(void)> CZoneScript::_LoadMakingArrowInfo(SERVER, "CZoneScript::LoadMakingArrowInfo");
int CZoneScript::LoadMakingArrowInfo(void) // line 107
{
	return (this->*_LoadMakingArrowInfo)();

	//TODO
}


hook_method<int (CZoneScript::*)(void)> CZoneScript::_Load_MK_ElementalInfo(SERVER, "CZoneScript::Load_MK_ElementalInfo");
int CZoneScript::Load_MK_ElementalInfo(void) // line 156
{
	return (this->*_Load_MK_ElementalInfo)();

	//TODO
}


hook_method<int (CZoneScript::*)(void)> CZoneScript::_Load_MK_CookInfo(SERVER, "CZoneScript::Load_MK_CookInfo");
int CZoneScript::Load_MK_CookInfo(void) // line 204
{
	return (this->*_Load_MK_CookInfo)();

	//TODO
}


hook_method<int (CZoneScript::*)(const char* fileName)> CZoneScript::_LoadItemGroupInfo(SERVER, "CZoneScript::LoadItemGroupInfo");
int CZoneScript::LoadItemGroupInfo(const char* fileName) // line 291
{
	return (this->*_LoadItemGroupInfo)(fileName);

	//TODO
}


hook_method<int (CZoneScript::*)(const char* fName)> CZoneScript::_LoadHomunInfo(SERVER, "CZoneScript::LoadHomunInfo");
int CZoneScript::LoadHomunInfo(const char* fName) // line 360
{
	return (this->*_LoadHomunInfo)(fName);

	//TODO
}


/// Checks if the specified account name is in the list of account names having the specified privilege.
/// @param id account name
/// @param func type of privilege to check
/// @return 1 if the account has this privilege, and 0 otherwise.
hook_method<int (CZoneScript::*)(char* id, enum MYCHECK_TYPE func)> CZoneScript::_CheckAvaibleID(SERVER, "CZoneScript::CheckAvaibleID");
int CZoneScript::CheckAvaibleID(char* id, enum MYCHECK_TYPE func) // line 460
{
	return (this->*_CheckAvaibleID)(id, func);

	if( id == NULL )
		return 0;

	mystd::list<mystd::string>::iterator it;
	for( it = m_idTable[func].begin(); it != m_idTable[func].end(); ++it )
		if( !strncmp(it->c_str(), id, 24) )
			break;

	return ( it != m_idTable[func].end() ) ? 1 : 0;
}


hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadIDTable(SERVER, "CZoneScript::LoadIDTable");
void CZoneScript::LoadIDTable(void) // line 495
{
	return (this->*_LoadIDTable)();

	//TODO
}


hook_method<void (CZoneScript::*)(void)> CZoneScript::_ClearIDTable(SERVER, "CZoneScript::ClearIDTable");
void CZoneScript::ClearIDTable(void) // line 541
{
	return (this->*_ClearIDTable)();

	//TODO
}


/*hook_method<void (CZoneScript::*)(void)> CZoneScript::_LoadAIDTable(SERVER, "CZoneScript::LoadAIDTable");
void CZoneScript::LoadAIDTable(void) // line ???
{
	return (this->*_LoadAIDTable)();

	//TODO
}*/


hook_method<int (CZoneScript::*)(char* itmName)> CZoneScript::_GetITMGroupID(SERVER, "CZoneScript::GetITMGroupID");
int CZoneScript::GetITMGroupID(char* itmName) // line 615
{
	return (this->*_GetITMGroupID)(itmName);

	//TODO
}


////////////////////////////////////////


CMatchTable::CMatchTable(void) // line 1097-1098
{
}


CMatchTable::~CMatchTable(void) // line 1101-1109
{
	while( m_matchMap.size() != 0 )
	{
		mystd::map<int,mystd::vector<int>*>::iterator it = m_matchMap.begin();

		if( it->second != NULL )
			delete it->second;

		m_matchMap.erase(it);
	}
}


hook_method<void (CMatchTable::*)(const char* fileName)> CMatchTable::_LoadFromFile(SERVER, "CMatchTable::LoadFromFile");
void CMatchTable::LoadFromFile(const char* fileName) // line 1112-1195
{
	return (this->*_LoadFromFile)(fileName);

	FILE* fp = fopen(fileName, "r");
	if( fp == NULL )
		return;

	while( !feof(fp) )
	{
		char buff[512];
		if( !fgets(buff, sizeof(buff), fp) )
			continue;

		bool bFirstStartFound = false;
		bool bFirstEndFound = false;
		bool bSecondStartFound = false;
		char buf1[512];
		char buf2[512];
		int j;

		for( int i = 0; i < sizeof(buff); ++i )
		{
			// seek past leading whitespace
			if( !bFirstStartFound )
			{
				if( buff[i] != ' ' && buff[i] != '\n' && buff[i] != '\t' )
					bFirstStartFound = true;

				continue;
			}

			// find next whitespace and copy everything until then into 'buf1'
			if( !bFirstEndFound )
			{
				if( buff[i] != ' ' && buff[i] != '\n' && buff[i] != '\t' )
					continue;

				bFirstEndFound = true;
				memcpy(buf1, buff, i + 1);
				buf1[i] = '\0';
				continue;
			}

			if( !bSecondStartFound )
			{
				bSecondStartFound = true;
				j = i;
				continue;
			}

			// find next whitespace and copy everything inbetween into 'buf2'
			if( bSecondStartFound )
			{
				if( buff[i] != ' ' && buff[i] != '\n' && buff[i] != '\t' )
					continue;

				memcpy(buf2, buff + j, i + 1); //FIXME: copy-paste typo, reads past buffer end, should be 'i - j + 1'
				buf2[i - j] = '\0';
				break;
			}
		}

		if( !bFirstEndFound )
		{
			char buff3[255];
			sprintf(buff3, "Wrong Match File Format! filename :%s\n", fileName);
			Trace(buff3);
		}

		int keyID = this->StringToKey(buf1);
		int destID = this->StringToDest(buf2);

		mystd::map<int,mystd::vector<int>*>::iterator k = m_matchMap.find(keyID);
		if( k == m_matchMap.end() )
		{
			mystd::vector<int>* v = new mystd::vector<int>;
			v->push_back(destID);

			m_matchMap[keyID] = v;
		}
		else
		{
			mystd::vector<int>* v = k->second;
			v->push_back(destID);
		}
	}

	fclose(fp);
}


hook_method<int (CMatchTable::*)(int n)> CMatchTable::_GetRandomMatch(SERVER, "CMatchTable::GetRandomMatch");
int CMatchTable::GetRandomMatch(int n) // line 1198-1214
{
	return (this->*_GetRandomMatch)(n);

	mystd::map<int,mystd::vector<int>*>::iterator i = m_matchMap.find(n);
	if( i == m_matchMap.end() )
		return -1;

	mystd::vector<int>* v = i->second;
	size_t size = v->size();
	if( size <= 0 )
		return -1;

	int pos = GetServerRandom(0, size - 1);
	return v->at(pos);
}


////////////////////////////////////////


CSummonItemTable& g_summonItemTable = *(CSummonItemTable*)DetourFindFunction(SERVER, "g_summonItemTable"); // line 1216


hook_method<int (CSummonItemTable::*)(char* keyString)> CSummonItemTable::_StringToKey(SERVER, "CSummonItemTable::StringToKey");
int CSummonItemTable::StringToKey(char* keyString) // line 1218-1221
{
	return (this->*_StringToKey)(keyString);

	return g_itpMgr->CITPMgr::GetITID(keyString);
}


hook_method<int (CSummonItemTable::*)(char* destString)> CSummonItemTable::_StringToDest(SERVER, "CSummonItemTable::StringToDest");
int CSummonItemTable::StringToDest(char* destString) // line 1224-1228
{
	return (this->*_StringToDest)(destString);

	return atoi(destString);
}


////////////////////////////////////////


CSummonMobBySkillTable& g_summonMobBySkillTable = *(CSummonMobBySkillTable*)DetourFindFunction(SERVER, "g_summonMobBySkillTable"); // line 1230


hook_method<int (CSummonMobBySkillTable::*)(char* keyString)> CSummonMobBySkillTable::_StringToKey(SERVER, "CSummonMobBySkillTable::StringToKey");
int CSummonMobBySkillTable::StringToKey(char* keyString) // line 1232-1235
{
	return (this->*_StringToKey)(keyString);

	return g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetSKID(keyString);
}


hook_method<int (CSummonMobBySkillTable::*)(char* destString)> CSummonMobBySkillTable::_StringToDest(SERVER, "CSummonMobBySkillTable::StringToDest");
int CSummonMobBySkillTable::StringToDest(char* destString) // line 1238-1239
{
	return (this->*_StringToDest)(destString);

	return g_monParameter->CMonParameterMgr::SearchKeyword(destString);
}
