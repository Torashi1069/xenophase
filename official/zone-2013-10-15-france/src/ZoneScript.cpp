#include "Enum.h"
#include "ITPMgr.h"
#include "MapTypeProperty.h"
#include "MonParameterMgr.h"
#include "Path.h"
#include "RuneItemInfo.h"
#include "SkillTypeInfoMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "ZoneScript.h"
////////////////////////////////////////


CZoneScript::CZoneScript()
{
}


CZoneScript::~CZoneScript()
{
	this->CZoneScript::Reset();
}


void CZoneScript::Init()
{
	this->CZoneScript::LoadMakingArrowInfo();
	this->CZoneScript::Load_MK_ElementalInfo();
	this->CZoneScript::Load_MK_CookInfo();
	this->CZoneScript::LoadIDTable();

	m_attackPlusPowerInfo = new CAttackPlusPowerInfo();
	m_attackPlusPowerInfo->CAttackPlusPowerInfo::Init(g_pathData.CPathData::SetFileName("attsuccesspercentinfo.scp"));

	this->CZoneScript::LoadMetamorphosisInfo();
	this->CZoneScript::LoadSummonSlaveInfo();
	this->CZoneScript::LoadMobEmotionInfo();
	this->CZoneScript::LoadAbracadabraInfo();

	m_itmGroupName["ITMGROUP_ORE"] = ITMGROUP_ORE;
	m_itmGroupName["ITMGROUP_GEM"] = ITMGROUP_GEM;
	m_itmGroupName["ITMGROUP_HEAL"] = ITMGROUP_HEAL;
	m_itmGroupName["ITMGROUP_FOOD"] = ITMGROUP_FOOD;

	if( !this->CZoneScript::LoadItemGroupInfo(g_pathData.CPathData::SetFileName("ItemGroupList.txt"))
	||  !this->CZoneScript::LoadHomunInfo(g_pathData.CPathData::SetFileName("Homun.scp")) )
	{
		ExitProcess(EXIT_SUCCESS);
	}

	if( !g_runeItemInfo.CRuneItemInfo::Init() )
	{
		MessageBoxA(NULL, "Initialize error", "g_runeItemInfo", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}
}


void CZoneScript::Reset()
{
	m_makingArrowInfo.clear();
	m_makeElemental.clear();

	for( size_t i = 0; i < countof(m_makeCook); ++i )
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
	m_HomunLevelUpTbl.clear();
	m_HomunEvolutionTbl.clear();
	m_HomunMutationTbl.clear();
}


BOOL CZoneScript::LoadMakingArrowInfo()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("mkArrow.txt"), "rt");
	if( fp == NULL )
	{
		MessageBoxA(NULL, "Error", "Load mkArrow.txt Failed!", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}

	std::vector<extraITMInfo> arrowItemList;

	while( 1 )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == -1 )
		{
			fclose(fp);
			return TRUE; // done.
		}

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
		}
		else
		if( strstr(buf, "/*") != NULL )
		{
			while( 1 )
			{
				if( fscanf(fp, "%s", buf) == -1 )
				{
					fclose(fp);
					return TRUE;
				}

				if( strstr(buf, "*/") != NULL )
					break;
			}
		}
		else
		{
			int useItemID = atoi(buf);

			for( int i = 0; i < 3; ++i )
			{
				extraITMInfo arrowItem;

				fscanf(fp, "%s", buf);
				arrowItem.id = atoi(buf);
				if( arrowItem.id == 0 )
					break;

				fscanf(fp, "%s", buf);
				arrowItem.num = atoi(buf);

				arrowItemList.push_back(arrowItem);
			}

			m_makingArrowInfo.insert(std::make_pair(useItemID, arrowItemList));
			arrowItemList.clear();
		}
	}
}


BOOL CZoneScript::Load_MK_ElementalInfo()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("mkElemental.txt"), "rt");
	if( fp == NULL )
	{
		MessageBoxA(NULL, "Error", "Load mkElemental.txt Failed!", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}

	std::vector<extraITMInfo> elementalList;

	while( 1 )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == -1 )
		{
			fclose(fp);
			return TRUE; // done.
		}

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
		}
		else
		if( strstr(buf, "/*") != NULL )
		{
			while( 1 )
			{
				if( fscanf(fp, "%s", buf) == -1 )
				{
					fclose(fp);
					return FALSE;
				}

				if( strstr(buf, "*/") != NULL )
					break;
			}
		}
		else
		{
			int elementalID = atoi(buf);

			for( int i = 0; i < 3; ++i )
			{
				extraITMInfo extraItem;

				fscanf(fp, "%s", buf);
				extraItem.id = atoi(buf);

				if( extraItem.id == 0 )
					break;

				fscanf(fp, "%s", buf);
				extraItem.num = atoi(buf);

				elementalList.push_back(extraItem);
			}

			m_makeElemental.insert(std::make_pair(elementalID, elementalList));
			elementalList.clear();
		}
	}
}


BOOL CZoneScript::Load_MK_CookInfo()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("mkCook.txt"), "rt");
	if( fp == NULL )
	{
		MessageBoxA(NULL, "Error", "Load mkCook.txt Failed!", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}

	std::vector<extraITMInfo> stuffList;
	unsigned short cookID = 0;
	int level = 0;
	short blkCnt = 0;

	while( 1 )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == -1 )
		{
			fclose(fp);
			return TRUE; // done.
		}

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
		}
		else
		if( strcmp(buf, "{") == 0 )
		{
			++blkCnt;
			stuffList.clear();
		}
		else
		if( strcmp(buf, "}") == 0 )
		{
			--blkCnt;
			m_makeCook[level - 1].insert(std::make_pair(cookID, stuffList));
		}
		else
		{
			if( blkCnt == 0 )
			{
				const char* p = strstr(buf, "#");
				if( p != NULL )
				{// #level
					level = atoi(p + 1);
				}
				else
				{// food item name
					cookID = g_itpMgr.CITPMgr::GetITID(buf);
					if( cookID == 0 )
					{
						char msg[256];
						sprintf_s(msg, countof(msg), "not exist ItemName!! (%s)", buf);
						MessageBoxA(NULL, msg, "mkCook.txt", MB_OK);
						ExitProcess(EXIT_SUCCESS);
					}
				}
			}
			else
			{// ingredient item name and count
				extraITMInfo extraItem;

				extraItem.id = g_itpMgr.CITPMgr::GetITID(buf);
				if( extraItem.id == 0 )
				{
					char msg[256];
					sprintf_s(msg, countof(msg), "not exist ItemName!! (%s)", buf);
					MessageBoxA(NULL, msg, "mkCook.txt", MB_OK);
					ExitProcess(EXIT_SUCCESS);
				}

				fscanf(fp, "%s", buf);
				extraItem.num = atoi(buf);

				stuffList.push_back(extraItem);
			}
		}
	}
}


BOOL CZoneScript::LoadItemGroupInfo(const char* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	if( fp == NULL )
	{
		char msg[256];
		sprintf_s(msg, countof(msg), "File not found! (%s)", fileName);
		MessageBoxA(NULL, "Error", msg, MB_OK);
		return FALSE;
	}

	std::vector<extraITMInfo> groupList;
	int blockCount = 0;
	int groupID = 0;

	while( 1 )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == -1 )
		{
			fclose(fp);
			return TRUE; // done.
		}

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
		}
		else
		if( strcmp(buf, "{") == 0 )
		{
			if( blockCount > 0 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "Check this file.(%s)", fileName);
				MessageBoxA(NULL, msg, "syntax error!", MB_OK);
//				fclose(fp); //FIXME
				return FALSE;
			}

			++blockCount;
			groupList.clear();
		}
		else
		if( strcmp(buf, "}") == 0 )
		{
			if( blockCount <= 0 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "Check this file.(%s)", fileName);
				MessageBoxA(NULL, msg, "syntax error!", MB_OK);
//				fclose(fp); //FIXME
				return FALSE;
			}

			--blockCount;
			m_itmGroupInfo.insert(std::make_pair(groupID, groupList));
		}
		else
		{
			if( blockCount == 0 )
			{
				groupID = this->CZoneScript::GetITMGroupID(buf);
				if( groupID == 0 )
				{
					char msg[256];
					sprintf_s(msg, countof(msg), "Not exist ItemGroupID!! (%s)", buf);
					MessageBoxA(NULL, msg, "ItemGroupList", MB_OK);
//					fclose(fp); //FIXME
					return FALSE;
				}
			}
			else
			{
				unsigned short ITID = g_itpMgr.CITPMgr::GetITID(buf);
				if( ITID == 0 )
				{
					char msg[256];
					sprintf_s(msg, countof(msg), "not exist ItemName!! (%s)", buf);
					MessageBoxA(NULL, msg, "ItemGroupList", MB_OK);
//					fclose(fp); //FIXME
					return FALSE;
				}

				fscanf(fp, "%s", buf);
				unsigned short num = (unsigned short)atoi(buf);

				extraITMInfo info;
				info.id = ITID;
				info.num = num;
				groupList.push_back(info);
			}
		}
	}
}


bool CZoneScript::LoadHomunStatTable(lua_State* L, const char* in_TblName, const short in_Job, HOMUN_STAT_CONTAINER& io_Tbl)
{
	char errormsg[256] = {};

	lua_getfield(L, LUA_GLOBALSINDEX, in_TblName);
	if( lua_type(L, -1) != LUA_TTABLE )
	{
		sprintf_s(errormsg, countof(errormsg), "[%s] is not a table", in_TblName);
		MessageBoxA(NULL, errormsg, "ERROR Homun.scp", MB_OK);
		lua_close(L);
		return false;
	}

	STAT_PLUSTABLE statInfo;
	statInfo.maxHP.min = this->CZoneScript::GetField(L, "MIN_MAXHP");
	statInfo.maxHP.max = this->CZoneScript::GetField(L, "MAX_MAXHP");
	statInfo.maxSP.min = this->CZoneScript::GetField(L, "MIN_MAXSP");
	statInfo.maxSP.max = this->CZoneScript::GetField(L, "MAX_MAXSP");
	statInfo.Str.min = this->CZoneScript::GetField(L, "MIN_STR");
	statInfo.Str.max = this->CZoneScript::GetField(L, "MAX_STR");
	statInfo.Int.min = this->CZoneScript::GetField(L, "MIN_INT");
	statInfo.Int.max = this->CZoneScript::GetField(L, "MAX_INT");
	statInfo.Vit.min = this->CZoneScript::GetField(L, "MIN_VIT");
	statInfo.Vit.max = this->CZoneScript::GetField(L, "MAX_VIT");
	statInfo.Dex.min = this->CZoneScript::GetField(L, "MIN_DEX");
	statInfo.Dex.max = this->CZoneScript::GetField(L, "MAX_DEX");
	statInfo.Agi.min = this->CZoneScript::GetField(L, "MIN_AGI");
	statInfo.Agi.max = this->CZoneScript::GetField(L, "MAX_AGI");
	statInfo.Luk.min = this->CZoneScript::GetField(L, "MIN_LUK");
	statInfo.Luk.max = this->CZoneScript::GetField(L, "MAX_LUK");

	std::pair<HOMUN_STAT_CONTAINER::iterator,bool> ret = io_Tbl.insert(std::make_pair(in_Job, statInfo));
	if( !ret.second )
	{
		sprintf_s(errormsg, countof(errormsg), "[%s], cannot insert table", in_TblName);
		MessageBoxA(NULL, errormsg, "ERROR Homun.scp", MB_OK);
		lua_close(L);
		return false;
	}

	return true;
}


BOOL CZoneScript::LoadHomunInfo(const char* fName)
{
	if( fName == NULL )
		return FALSE;

	lua_State* L = luaL_newstate();
	if( L == NULL )
		return FALSE;

	if( luaL_loadfile(L, fName) != 0 || lua_pcall(L, 0, 0, 0) != 0 )
	{
		char buf[256] = {};
		sprintf_s(buf, countof(buf), "cannot run file: %s", lua_tolstring(L, -1, NULL));
		MessageBoxA(NULL, buf, "BOOL CZoneScript :: LoadHomunInfo", MB_OK);
		lua_close(L);
		return FALSE;
	}

	if( !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_LIF", JT_MER_LIF, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_AMISTR", JT_MER_AMISTR, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_FILIR", JT_MER_FILIR, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_VANILMIRTH", JT_MER_VANILMIRTH, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_EIRA", JT_MER_EIRA, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_BAYERI", JT_MER_BAYERI, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_SERA", JT_MER_SERA, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_DIETER", JT_MER_DIETER, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "StatusTBL_ELEANOR", JT_MER_ELEANOR, m_HomunLevelUpTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "EvolutaionTBL_LIF", JT_MER_LIF, m_HomunEvolutionTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "EvolutaionTBL_AMISTR", JT_MER_AMISTR, m_HomunEvolutionTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "EvolutaionTBL_FILIR", JT_MER_FILIR, m_HomunEvolutionTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "EvolutaionTBL_VANILMIRTH", JT_MER_VANILMIRTH, m_HomunEvolutionTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "MutationTBL_EIRA", JT_MER_EIRA, m_HomunMutationTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "MutationTBL_BAYERI", JT_MER_BAYERI, m_HomunMutationTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "MutationTBL_SERA", JT_MER_SERA, m_HomunMutationTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "MutationTBL_DIETER", JT_MER_DIETER, m_HomunMutationTbl)
	 || !this->CZoneScript::LoadHomunStatTable(L, "MutationTBL_ELEANOR", JT_MER_ELEANOR, m_HomunMutationTbl) )
	{
//		lua_close(L); //FIXME
		return FALSE;
	}

	lua_close(L);
	return TRUE;
}


int CZoneScript::GetField(lua_State* L, const char* key)
{
	lua_pushstring(L, key);
	lua_gettable(L, -2);

	if( !lua_isnumber(L, -1) )
		return 0;

	int result = (int)lua_tonumber(L, -1);

	lua_settop(L, -2);

	return result;
}


const STAT_PLUSTABLE* CZoneScript::GetHomunMutationStatTable(const int in_Job)
{
	short index;
	if( in_Job < JT_MER_LIF || in_Job > JT_MER_VANILMIRTH_H2 )
		index = in_Job; //FIXME: should return NULL instead
	else
		index = JT_MER_LIF + (in_Job - JT_MER_LIF) % 4;

	HOMUN_STAT_CONTAINER::const_iterator iter = m_HomunLevelUpTbl.find(index);
	if( iter == m_HomunLevelUpTbl.end() )
		return NULL;

	return &iter->second;
}


const STAT_PLUSTABLE* CZoneScript::GetHomunEvolutionStatTable(const int in_Job)
{
	if( in_Job < JT_MER_LIF || in_Job > JT_MER_VANILMIRTH_H2 )
		return NULL;

	short index = JT_MER_LIF + (in_Job - JT_MER_LIF) % 4;

	HOMUN_STAT_CONTAINER::const_iterator iter = m_HomunEvolutionTbl.find(index);
	if( iter == m_HomunEvolutionTbl.end() )
		return NULL;

	return &iter->second;
}


const STAT_PLUSTABLE* CZoneScript::GetHomunLevelUpStatTable(const int in_Job)
{
	if( in_Job < JT_MER_EIRA || in_Job > JT_MER_ELEANOR )
		return NULL;

	HOMUN_STAT_CONTAINER::const_iterator iter = m_HomunMutationTbl.find(in_Job);
	if( iter == m_HomunMutationTbl.end() )
		return NULL;

	return &iter->second;
}


BOOL CZoneScript::CheckAvaibleID(char* id, MYCHECK_TYPE func)
{
	if( id == NULL )
		return FALSE;

	for( std::list<std::string>::const_iterator iter = m_idTable[func].begin(); iter != m_idTable[func].end(); ++iter )
		if( strncmp(iter->c_str(), id, 24) == 0 )
			return TRUE; // found.

	return FALSE; // not found.
}


BOOL CZoneScript::SearchID(char* id, MYCHECK_TYPE func)
{
	if( id == NULL )
		return FALSE;

	if( func < CHECK_LOCALBROADCAST || func > CHECK_GMDEFANS )
		return FALSE;

	return this->CZoneScript::CheckAvaibleID(id, func);
}


void CZoneScript::LoadIDTable()
{
	this->CZoneScript::ClearIDTable();

	FILE* fp = fopen(g_pathData.CPathData::SetFileName("idtable.txt"), "r");
	if( fp == NULL )
		return;

	int iCheckType = -1;
	while( !feof(fp) )
	{
		char buf[512];
		fscanf(fp, "%s", buf);

		if( strstr(buf, "//") != NULL )
		{// comment
			fgets(buf, 100, fp);
		}
		else
		if( strcmp(buf, "*") == 0 )
		{// ???
			break;
		}
		else
		if( strstr(buf, "[") != NULL )
		{// type
			const char* p = buf + 1;
			iCheckType = atoi(p);
			while( *p != ']' )
				++p;
		}
		else
		if( strcmp(buf, "::") == 0 )
		{// ???
		}
		else
		if( iCheckType != -1 && iCheckType < CHECK_MAX_NUM )
		{// account name
			m_idTable[iCheckType].push_back(buf);
		}
		else
		{// junk
			fgets(buf, 100, fp);
		}
	}

	fclose(fp);
}


void CZoneScript::ClearIDTable()
{
	for( size_t i = 0; i < countof(m_idTable); ++i )
		m_idTable[i].clear();
}


void CZoneScript::LoadAIDTable()
{
	m_aidTable.clear();

	FILE* fp = fopen("aidtable.txt", "r");
	if( fp == NULL )
		return;

	while( !feof(fp) )
	{
		char buf[512];
		fscanf(fp, "%s", buf);

		if( strstr(buf, "//") != NULL )
		{// comment
			fgets(buf, 100, fp);
		}
		else
		if( strcmp(buf, "*") == 0 )
		{// ???
			break;
		}
		else
		if( strcmp(buf, "[AID_LIST]") == 0 )
		{// aid list
			while( fscanf(fp, "%s", buf) != -1 )
			{
				unsigned long AID = atoi(buf);
				m_aidTable.push_back(AID);
			}
		}
	}

	fclose(fp);
}


unsigned long CZoneScript::GetCatchAID()
{
	if( m_aidTable.size() == 0 )
		return 0;

	unsigned long AID = m_aidTable.front();

	m_aidTable.erase(m_aidTable.begin());
	m_aidTable.push_back(AID);

	return AID;
}


unsigned long CZoneScript::GetRemoveCatchAID()
{
	if( m_aidTable.size() <= 1 )
		return 0;

	return m_aidTable.back();
}


BOOL CZoneScript::CheckAID(unsigned long AID)
{
	std::list<unsigned long>::iterator iter = std::find(m_aidTable.begin(), m_aidTable.end(), AID);
	return ( iter != m_aidTable.end() );
}


int CZoneScript::GetITMGroupID(char* itmName)
{
	std::map<std::string,int>::iterator iter = m_itmGroupName.find(itmName);
	if( iter == m_itmGroupName.end() )
		return 0;

	return iter->second;
}


unsigned long CZoneScript::GetITMFromGroupID(int groupID)
{
	std::map<int,std::vector<extraITMInfo>>::iterator iter = m_itmGroupInfo.find(groupID);
	if( iter == m_itmGroupInfo.end() )
		return 0;
	
	int index = GetServerRandom(0, 20000) % iter->second.size();
	extraITMInfo* info = &iter->second[index];

	if( GetServerRandom(0, 20000) % 10000 >= info->num )
		return 0; // random attempt failed.

	return info->id;
}


void CZoneScript::LoadMetamorphosisInfo()
{
	m_metamorphosisInfo.clear();
	this->CZoneScript::LoadSummonMobInfo(g_pathData.CPathData::SetFileName("MetamorphosisInfo.scp"), m_metamorphosisInfo);
}


SummonMobList* CZoneScript::GetMetamorphosis(unsigned long spriteType)
{
	std::map<unsigned long,SummonMobList>::iterator iter = m_metamorphosisInfo.find(spriteType);
	if( iter == m_metamorphosisInfo.end() )
		return NULL;

	return &iter->second;
}


void CZoneScript::LoadSummonSlaveInfo()
{
	m_summonSlaveInfo.clear();
	this->CZoneScript::LoadSummonMobInfo(g_pathData.CPathData::SetFileName("SlaveSummonInfo.scp"), m_summonSlaveInfo);
}


SummonMobList* CZoneScript::GetSummonSlaveList(unsigned long spriteType)
{
	std::map<unsigned long,SummonMobList>::iterator iter = m_summonSlaveInfo.find(spriteType);
	if( iter == m_summonSlaveInfo.end() )
		return NULL;

	return &iter->second;
}


void CZoneScript::LoadSummonMobInfo(const char* filename, std::map<unsigned long,SummonMobList>& summonMobInfo)
{
	FILE* fp = fopen(filename, "r");
	if( fp == NULL )
		return;

	SummonMobList tempSlaveMobList;
	BOOL result = FALSE;

	while( 1 )
	{
		if( feof(fp) )
		{
			fclose(fp);
			return;
		}

		char strBuf[512];
		fscanf(fp, "%s", strBuf);

		if( strstr(strBuf, "//") != NULL )
		{
			fgets(strBuf, countof(strBuf), fp);
			continue;
		}

		unsigned long spriteType = g_monParameter.CMonParameterMgr::SearchKeyword(strBuf);
		if( spriteType == -1 )
		{
			fgets(strBuf, countof(strBuf), fp);
			continue;
		}

		tempSlaveMobList.num = 0;
		tempSlaveMobList.summonMob.clear();

		while( !feof(fp) )
		{
			fscanf(fp, "%s", strBuf);

			unsigned long slaveType = g_monParameter.CMonParameterMgr::SearchKeyword(strBuf);
			if( slaveType == -1 )
			{
				int num = atoi(strBuf);
				if( num != 0 )
				{
					tempSlaveMobList.num = num;
					result = TRUE;
				}

				break;
			}

			tempSlaveMobList.summonMob.push_back(slaveType);
		}

		if( result )
			summonMobInfo.insert(std::make_pair(spriteType, tempSlaveMobList));
	}
}


void CZoneScript::LoadMobEmotionInfo()
{
	m_mobEmotionInfo.clear();

	FILE* fp = fopen(g_pathData.CPathData::SetFileName("MobEmotionInfo.scp"), "r");
	if( fp == NULL )
		return;

	while( !feof(fp) )
	{
		char strBuf[256];
		fgets(strBuf, countof(strBuf), fp);

		if( strstr(strBuf, "//") != NULL )
			continue;

		char strName[256];
		char strEmotion[128];
		sscanf(strBuf, "%s %s", strName, strEmotion);

		unsigned long job = g_monParameter.CMonParameterMgr::SearchKeyword(strName);
		if( job == -1 )
			continue;

		int emotion = atoi(strEmotion);

		m_mobEmotionInfo.insert(std::make_pair(job, emotion));
	}

	fclose(fp);
}


int CZoneScript::GetMobEmotion(unsigned long spriteType)
{
	std::map<unsigned long,int>::iterator iter = m_mobEmotionInfo.find(spriteType);
	if( iter == m_mobEmotionInfo.end() )
		return -1;

	return iter->second;
}


void CZoneScript::LoadAbracadabraInfo()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("AbracadabraInfo.scp"), "r");
	if( fp == NULL )
	{
		MessageBoxA(NULL, "Load AbracadabraInfo.scp Failed!", "Error", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}

	std::map<unsigned short,short> skillPInfo;
	char strBuf[256];

	while( !feof(fp) )
	{
		fscanf(fp, "%s", strBuf);
		if( strstr(strBuf, "//") != NULL )
		{
			fgets(strBuf, 256, fp);
			continue;
		}

		unsigned short SKID = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSKID(strBuf);
		if( SKID == 0 )
			continue;

		for( int level = 1; level <= 10; ++level )
		{
			fscanf(fp, "%s", strBuf);

			short rate = (short)atoi(strBuf);
			if( rate == 0 )
				continue;

			std::map<short,std::map<unsigned short,short>>::iterator iter = m_abracadabraInfo.find(level);
			if( iter == m_abracadabraInfo.end() )
			{
				skillPInfo.clear();
				skillPInfo.insert(std::make_pair(SKID, rate));
				m_abracadabraInfo.insert(std::make_pair(level, skillPInfo));
			}
			else
			{
				iter->second.insert(std::make_pair(SKID, rate));
			}
		}
	}

	fclose(fp);
}


unsigned short CZoneScript::GetSkillByAbracadabra(short level)
{
	std::map<short,std::map<unsigned short,short>>::iterator iter = m_abracadabraInfo.find(level);
	if( iter == m_abracadabraInfo.end() )
		return 0;
	
	for( std::map<unsigned short,short>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2 )
	{
		unsigned short SKID = iter2->first;
		short rate = iter2->second;

		if( GetServerRandom(0, 20000) % 10000 < rate )
			return SKID;
	}

	return 0; // failed all random attempts.
}


std::map<unsigned short,std::vector<extraITMInfo>> CZoneScript::GetMakingArrowItemInfo()
{
	return m_makingArrowInfo;
}


std::map<unsigned short,std::vector<extraITMInfo>> CZoneScript::GetMakingElementalInfo()
{
	return m_makeElemental;
}


std::map<unsigned short,std::vector<extraITMInfo>> CZoneScript::GetMakingCookInfo(short level)
{
	return m_makeCook[level];
}


int CZoneScript::GetAtkPlusPWByProperty(int defState, int atkState)
{
	if( m_attackPlusPowerInfo != NULL )
		return m_attackPlusPowerInfo->CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(defState, atkState);
	else
		return 0;
}


void CZoneScript::GetAtkPlusPWByProperty(int defState, int atkState, int& result)
{
	if( m_attackPlusPowerInfo != NULL )
		m_attackPlusPowerInfo->CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(defState, atkState, result);
	else
		result = 0;
}


int CZoneScript::GetAtkPlusPWByProperty_Variation(int defState, int atkState, int in_damage)
{
	if( m_attackPlusPowerInfo != NULL )
		return m_attackPlusPowerInfo->CAttackPlusPowerInfo::GetAttackPlusPowerByProperty_Variation(defState, atkState, in_damage);
	else
		return 0;
}


////////////////////////////////////////


CAttackPlusPowerInfo::CAttackPlusPowerInfo()
{
}


CAttackPlusPowerInfo::~CAttackPlusPowerInfo()
{
}


int CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(int defState, int atkState)
{
	if     ( defState >= PROPERTY_NOTHING  && defState <= PROPERTY_UNDEAD  ) return m_info[0].val[atkState][defState - PROPERTY_NOTHING ];
	else if( defState >= PROPERTY_NOTHING1 && defState <= PROPERTY_UNDEAD1 ) return m_info[1].val[atkState][defState - PROPERTY_NOTHING1];
	else if( defState >= PROPERTY_NOTHING2 && defState <= PROPERTY_UNDEAD2 ) return m_info[2].val[atkState][defState - PROPERTY_NOTHING2];
	else if( defState >= PROPERTY_NOTHING3 && defState <= PROPERTY_UNDEAD3 ) return m_info[3].val[atkState][defState - PROPERTY_NOTHING3];
	else if( defState >= PROPERTY_NOTHING4 && defState <= PROPERTY_UNDEAD4 ) return m_info[4].val[atkState][defState - PROPERTY_NOTHING4];
	else return 0;
}


void CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(int defState, int atkState, int& result)
{
	if     ( defState >= PROPERTY_NOTHING  && defState <= PROPERTY_UNDEAD  ) result = result * m_info[0].val[atkState][defState - PROPERTY_NOTHING ] / 100;
	else if( defState >= PROPERTY_NOTHING1 && defState <= PROPERTY_UNDEAD1 ) result = result * m_info[1].val[atkState][defState - PROPERTY_NOTHING1] / 100;
	else if( defState >= PROPERTY_NOTHING2 && defState <= PROPERTY_UNDEAD2 ) result = result * m_info[2].val[atkState][defState - PROPERTY_NOTHING2] / 100;
	else if( defState >= PROPERTY_NOTHING3 && defState <= PROPERTY_UNDEAD3 ) result = result * m_info[3].val[atkState][defState - PROPERTY_NOTHING3] / 100;
	else if( defState >= PROPERTY_NOTHING4 && defState <= PROPERTY_UNDEAD4 ) result = result * m_info[4].val[atkState][defState - PROPERTY_NOTHING4] / 100;
	else result = 0;
}


int CAttackPlusPowerInfo::GetAttackPlusPowerByProperty_Variation(int defState, int atkState, int in_damage)
{
	if     ( defState >= PROPERTY_NOTHING  && defState <= PROPERTY_UNDEAD  ) return in_damage * (m_info[0].val[atkState][defState - PROPERTY_NOTHING ] - 100) / 100;
	else if( defState >= PROPERTY_NOTHING1 && defState <= PROPERTY_UNDEAD1 ) return in_damage * (m_info[1].val[atkState][defState - PROPERTY_NOTHING1] - 100) / 100;
	else if( defState >= PROPERTY_NOTHING2 && defState <= PROPERTY_UNDEAD2 ) return in_damage * (m_info[2].val[atkState][defState - PROPERTY_NOTHING2] - 100) / 100;
	else if( defState >= PROPERTY_NOTHING3 && defState <= PROPERTY_UNDEAD3 ) return in_damage * (m_info[3].val[atkState][defState - PROPERTY_NOTHING3] - 100) / 100;
	else if( defState >= PROPERTY_NOTHING4 && defState <= PROPERTY_UNDEAD4 ) return in_damage * (m_info[4].val[atkState][defState - PROPERTY_NOTHING4] - 100) / 100;
	else return 0;
}


void CAttackPlusPowerInfo::Init(const char* filename)
{
	m_propertyName["NOTHING"] = PROPERTY_NOTHING;
	m_propertyName["WATER"] = PROPERTY_WATER;
	m_propertyName["GROUND"] = PROPERTY_GROUND;
	m_propertyName["FIRE"] = PROPERTY_FIRE;
	m_propertyName["WIND"] = PROPERTY_WIND;
	m_propertyName["POISON"] = PROPERTY_POISON;
	m_propertyName["SAINT"] = PROPERTY_SAINT;
	m_propertyName["DARKNESS"] = PROPERTY_DARKNESS;
	m_propertyName["TELEKINESIS"] = PROPERTY_TELEKINESIS;
	m_propertyName["UNDEAD"] = PROPERTY_UNDEAD;
	m_propertyName["NOTHING_1"] = PROPERTY_NOTHING1;
	m_propertyName["WATER_1"] = PROPERTY_WATER1;
	m_propertyName["GROUND_1"] = PROPERTY_GROUND1;
	m_propertyName["FIRE_1"] = PROPERTY_FIRE1;
	m_propertyName["WIND_1"] = PROPERTY_WIND1;
	m_propertyName["POISON_1"] = PROPERTY_POISON1;
	m_propertyName["SAINT_1"] = PROPERTY_SAINT1;
	m_propertyName["DARKNESS_1"] = PROPERTY_DARKNESS1;
	m_propertyName["TELEKINESIS_1"] = PROPERTY_TELEKINESIS1;
	m_propertyName["UNDEAD_1"] = PROPERTY_UNDEAD1;
	m_propertyName["NOTHING_2"] = PROPERTY_NOTHING2;
	m_propertyName["WATER_2"] = PROPERTY_WATER2;
	m_propertyName["GROUND_2"] = PROPERTY_GROUND2;
	m_propertyName["FIRE_2"] = PROPERTY_FIRE2;
	m_propertyName["WIND_2"] = PROPERTY_WIND2;
	m_propertyName["POISON_2"] = PROPERTY_POISON2;
	m_propertyName["SAINT_2"] = PROPERTY_SAINT2;
	m_propertyName["DARKNESS_2"] = PROPERTY_DARKNESS2;
	m_propertyName["TELEKINESIS_2"] = PROPERTY_TELEKINESIS2;
	m_propertyName["UNDEAD_2"] = PROPERTY_UNDEAD2;
	m_propertyName["NOTHING_3"] = PROPERTY_NOTHING3;
	m_propertyName["WATER_3"] = PROPERTY_WATER3;
	m_propertyName["GROUND_3"] = PROPERTY_GROUND3;
	m_propertyName["FIRE_3"] = PROPERTY_FIRE3;
	m_propertyName["WIND_3"] = PROPERTY_WIND3;
	m_propertyName["POISON_3"] = PROPERTY_POISON3;
	m_propertyName["SAINT_3"] = PROPERTY_SAINT3;
	m_propertyName["DARKNESS_3"] = PROPERTY_DARKNESS3;
	m_propertyName["TELEKINESIS_3"] = PROPERTY_TELEKINESIS3;
	m_propertyName["UNDEAD_3"] = PROPERTY_UNDEAD3;
	m_propertyName["NOTHING_4"] = PROPERTY_NOTHING4;
	m_propertyName["WATER_4"] = PROPERTY_WATER4;
	m_propertyName["GROUND_4"] = PROPERTY_GROUND4;
	m_propertyName["FIRE_4"] = PROPERTY_FIRE4;
	m_propertyName["WIND_4"] = PROPERTY_WIND4;
	m_propertyName["POISON_4"] = PROPERTY_POISON4;
	m_propertyName["SAINT_4"] = PROPERTY_SAINT4;
	m_propertyName["DARKNESS_4"] = PROPERTY_DARKNESS4;
	m_propertyName["TELEKINESIS_4"] = PROPERTY_TELEKINESIS4;
	m_propertyName["UNDEAD_4"] = PROPERTY_UNDEAD4;

	this->CAttackPlusPowerInfo::LoadScript(filename, 20020627);
}


int CAttackPlusPowerInfo::GetpropertyID(char* name)
{
	std::map<std::string,int>::iterator iter = m_propertyName.find(name);
	if( iter == m_propertyName.end() )
		return -1;

	return iter->second;
}


void CAttackPlusPowerInfo::LoadScript(const char* filename, int verDate)
{
	FILE* fp = fopen(filename, "rt");
	if( fp == NULL )
		ExitProcess(EXIT_FAILURE);

	int date;
	fscanf(fp, "%d\n", &date);

	if( date != verDate )
	{
		char buf[256];
		sprintf_s(buf, countof(buf), "%s old version?", filename);
		MessageBoxA(NULL, buf, "error", MB_OK);
	}

	int rowCnt = 0;
	int eleLv = 0;

	while( 1 )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == -1 )
		{
			fclose(fp);
			break; // done.
		}

		if( strstr(buf, "//") != NULL )
		{
			while( 1 )
			{
				int c = getc(fp);

				if( c == -1 )
				{
					fclose(fp);
					return; // error.
				}

				if( c == '\n' )
					break; // done.
			}
		}
		else
		if( strstr(buf, "/*") != NULL )
		{
			while( 1 )
			{
				if( fscanf(fp, "%s", buf) == -1 )
				{
					fclose(fp);
					return; // error.
				}

				if( strstr(buf, "*/") != NULL )
					break; // done.
			}
		}
		else
		{
			int attEle = this->CAttackPlusPowerInfo::GetpropertyID(buf);

			for( int defEle = 0; defEle < 10; ++defEle )
			{
				fscanf(fp, "%s", buf);
				m_info[eleLv].val[attEle][defEle] = atoi(buf);
			}

			++rowCnt;
			if( rowCnt >= 10 )
			{
				rowCnt = 0;
				++eleLv;
			}
		}
	}
}


void CAttackPlusPowerInfo::Reset()
{
	m_propertyName.clear();
}
