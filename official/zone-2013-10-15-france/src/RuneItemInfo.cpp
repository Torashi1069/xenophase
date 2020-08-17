#include "ITPMgr.h"
#include "Path.h"
#include "RuneItemInfo.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "shared/NCriticalErrorLog.h"


/// globals
CRuneItemInfo& g_runeItemInfo = VTOR<CRuneItemInfo>(DetourFindFunction(EXEPATH(), "g_runeItemInfo"));


CRuneItemInfo::CRuneItemInfo()
{
}


CRuneItemInfo::~CRuneItemInfo()
{
	m_ranktype.clear();
	m_runeRankList.clear();
	m_rankSuccessPercent.clear();
	m_rawRuneSuccessPercent.clear();
	m_runeMastery_MakeSuccessPercent.clear();
	m_runeMastery_MakeMinCount.clear();
	m_runeMastery_MakeMaxCount.clear();
	m_runeMastery_UseSuccessPercent.clear();
	m_runeMasteryLevel_MakableItem.clear();
	m_runeItem_MaxCount.clear();
	m_runeMaterials.clear();
}


bool CRuneItemInfo::Init()
{
	lua_State* L = luaL_newstate();
	if( L == NULL )
		return false;

	if( luaL_loadfile(L, g_pathData.CPathData::SetFileName("RuneItemInfo.lua")) != 0
	 || lua_pcall(L, 0, 0, 0) != 0
	 || !this->CRuneItemInfo::Load_RankType(L)
	 || !this->CRuneItemInfo::Load_RuneRankList(L)
	 || !this->CRuneItemInfo::Load_RankSuccessPercent(L)
	 || !this->CRuneItemInfo::Load_RawRundSuccessPercent(L)
	 || !this->CRuneItemInfo::Load_RuneMastery_MakeSuccessPercent(L)
	 || !this->CRuneItemInfo::Load_RuneMastery_MakeMinCount(L)
	 || !this->CRuneItemInfo::Load_RuneMastery_MakeMaxCount(L)
	 || !this->CRuneItemInfo::Load_RuneMastery_UseSuccessPercent(L)
	 || !this->CRuneItemInfo::Load_RuneMasteryLevel_MakableItem(L)
	 || !this->CRuneItemInfo::Load_RuneItem_MaxCount(L)
	 || !this->CRuneItemInfo::Load_RuneMaterial(L) )
	{
		lua_close(L);
		return false;
	}

	lua_close(L);
	return true;
}


bool CRuneItemInfo::Load_KeyValue(lua_State* L, const char* table, std::map<int,short>* _list)
{
	lua_getfield(L, LUA_GLOBALSINDEX, table);
	if( lua_type(L, -1) == LUA_TTABLE )
		return false;

	lua_pushnil(L);

	while( lua_next(L, -2) )
	{
		if( !lua_isstring(L, -2) || !lua_isnumber(L, -1) )
			return false;

		const char* key = lua_tolstring(L, -2, NULL);
		int value = (int)lua_tonumber(L, -1);
		lua_settop(L, -2);

		unsigned short ITID = g_itpMgr.CITPMgr::GetITID(key);
		if( ITID == 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown item [%s]", key);
			return false;
		}

		_list->insert(std::make_pair(ITID, value));
	}

	return true;
}


bool CRuneItemInfo::Load_KeyValue(lua_State* L, const char* table, std::map<std::string,short>* _list)
{
	lua_getfield(L, LUA_GLOBALSINDEX, table);
	if( lua_type(L, -1) != LUA_TTABLE )
		return false;

	lua_pushnil(L);

	while( lua_next(L, -2) )
	{
		if( !lua_isstring(L, -2) || !lua_isnumber(L, -1) )
			return false;

		const char* key = lua_tolstring(L, -2, NULL);
		int value = (int)lua_tonumber(L, -1);
		lua_settop(L, -2);

		_list->insert(std::make_pair(key, value));
	}

	return true;
}


bool CRuneItemInfo::Load_KeyValue(lua_State* L, const char* table, std::vector<short>* _list)
{
	lua_getfield(L, LUA_GLOBALSINDEX, table);
	if( lua_type(L, -1) != LUA_TTABLE )
		return false;

	lua_pushnil(L);

	while( lua_next(L, -2) )
	{
		if( !lua_isnumber(L, -2) || !lua_isnumber(L, -1) )
			return false;

		int key = (int)lua_tonumber(L, -2); // unused?
		int value = (int)lua_tonumber(L, -1);
		lua_settop(L, -2);

		_list->push_back(value);
	}

	if( _list->size() != 10 )
		return false;

	return true;
}


bool CRuneItemInfo::Load_KeyValue(lua_State* L, const char* table, std::list<RUNE_MATERIAL>* _list)
{
	lua_getfield(L, LUA_GLOBALSINDEX, table);
	if( lua_type(L, -1) != LUA_TTABLE )
		return false;

	lua_pushnil(L);

	while( lua_next(L, -2) )
	{
		if( !lua_isstring(L, -2) || !lua_isnumber(L, -1) )
			return 0;

		const char* key = lua_tolstring(L, -2, NULL);
		int value = (int)lua_tonumber(L, -1);
		lua_settop(L, -2);

		unsigned short ITID = g_itpMgr.CITPMgr::GetITID(key);

		RUNE_MATERIAL temp;
		temp.itemID = ITID;
		temp.count = value;

		if( ITID == 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown item [%s]", key);
			return false;
		}

		_list->push_back(temp);
	}

	return true;
}


bool CRuneItemInfo::Load_RankType(lua_State* L)
{
	return this->CRuneItemInfo::Load_KeyValue(L, "RankType", &m_ranktype);
}


bool CRuneItemInfo::Load_RuneRankList(lua_State* L)
{
	return this->CRuneItemInfo::Load_KeyValue(L, "RuneRankList", &m_runeRankList);
}


bool CRuneItemInfo::Load_RankSuccessPercent(lua_State* L)
{
	lua_getfield(L, LUA_GLOBALSINDEX, "RankSuccessPercent");
	if( lua_type(L, -1) != LUA_TTABLE )
		return false;

	lua_pushnil(L);

	while( lua_next(L, -2) )
	{
		if( !lua_isstring(L, -2) || !lua_isnumber(L, -1) )
			return false;

		const char* key = lua_tolstring(L, -2, NULL);
		int value = (int)lua_tonumber(L, -1);
		lua_settop(L, -2);

		std::map<std::string,short>::iterator iter = m_ranktype.find(key);
		if( iter == m_ranktype.end() )
			return false;

		short rankID = iter->second;

		m_rankSuccessPercent.insert(std::make_pair(rankID, value));
	}

	return true;
}


bool CRuneItemInfo::Load_RawRundSuccessPercent(lua_State* L)
{
	return this->CRuneItemInfo::Load_KeyValue(L, "RawRuneSuccessPercent", &m_rawRuneSuccessPercent);
}


bool CRuneItemInfo::Load_RuneMastery_MakeSuccessPercent(lua_State* L)
{
	return this->CRuneItemInfo::Load_KeyValue(L, "RuneMastery_MakeSuccessPercent", &m_runeMastery_MakeSuccessPercent);
}


bool CRuneItemInfo::Load_RuneMastery_MakeMinCount(lua_State* L)
{
	return this->CRuneItemInfo::Load_KeyValue(L, "RuneMastery_MakeMinCount", &m_runeMastery_MakeMinCount);
}


bool CRuneItemInfo::Load_RuneMastery_MakeMaxCount(lua_State* L)
{
	return this->CRuneItemInfo::Load_KeyValue(L, "RuneMastery_MakeMaxCount", &m_runeMastery_MakeMaxCount);
}


bool CRuneItemInfo::Load_RuneMastery_UseSuccessPercent(lua_State* L)
{
	return this->CRuneItemInfo::Load_KeyValue(L, "RuneMastery_UseSuccessPercent", &m_runeMastery_UseSuccessPercent);
}


bool CRuneItemInfo::Load_RuneMasteryLevel_MakableItem(lua_State* L)
{
	lua_getfield(L, LUA_GLOBALSINDEX, "RuneMasteryLevel_MakableItem");
	if( lua_type(L, -1) != LUA_TTABLE )
		return false;

	lua_pushnil(L);

	while( lua_next(L, -2) )
	{
		if( !lua_isnumber(L, -2) || !lua_isstring(L, -1) )
			return false;

		int key = (int)lua_tonumber(L, -2);
		const char* value = lua_tolstring(L, -1, NULL);
		lua_settop(L, -2);

		unsigned short ITID = g_itpMgr.CITPMgr::GetITID(value);

		if( ITID == 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown item [%s]", value);
			return false;
		}

		RUNE_ITEM temp;
		temp.itemID = ITID;
		temp.itemName = value;

		m_runeMasteryLevel_MakableItem.insert(std::make_pair(key, temp));
	}

	return true;
}


bool CRuneItemInfo::Load_RuneItem_MaxCount(lua_State* L)
{
	return this->CRuneItemInfo::Load_KeyValue(L, "RuneItem_MaxCount", &m_runeItem_MaxCount);
}


bool CRuneItemInfo::Load_RuneMaterial(lua_State* L)
{
	for( std::map<int,RUNE_ITEM>::iterator iter = m_runeMasteryLevel_MakableItem.begin(); iter != m_runeMasteryLevel_MakableItem.end(); ++iter )
	{
		RUNE_ITEM& item = iter->second;

		char table[256] = {};
		sprintf_s(table, countof(table), "Rune_%d", item.itemID);

		std::list<RUNE_MATERIAL> _list;
		if( !this->CRuneItemInfo::Load_KeyValue(L, table, &_list) )
			return false;

		std::pair<std::map<int,RUNE_MATERIAL_LIST>::iterator,bool> ret = m_runeMaterials.insert(std::make_pair(item.itemID, _list));
		if( !ret.second )
			return false;
	}

	return true;
}


CRuneItemInfo::RUNE_MATERIAL_LIST* CRuneItemInfo::GetRuneMaterial(int runeID)
{
	std::map<int,RUNE_MATERIAL_LIST>::iterator iter = m_runeMaterials.find(runeID);
	if( iter == m_runeMaterials.end() )
		return 0;

	return &iter->second;
}


int CRuneItemInfo::GetRawRuneSuccessPercent(int rawID)
{
	std::map<int,short>::iterator iter = m_rawRuneSuccessPercent.find(rawID);
	if( iter == m_rawRuneSuccessPercent.end() )
		return 0;

	return iter->second;
}


int CRuneItemInfo::GetRuneRankSuccessPercent(int runeID)
{
	std::map<int,short>::iterator iter = m_runeRankList.find(runeID);
	if( iter == m_runeRankList.end() )
		return 0;
	
	short rank = iter->second;

	std::map<short,short>::iterator _iter = m_rankSuccessPercent.find(rank);
	if( _iter == m_rankSuccessPercent.end() )
		return 0;

	short percent = _iter->second;

	return percent;
}


int CRuneItemInfo::GetMakableRuneItemByLevel(int skLevel)
{
	std::map<int,RUNE_ITEM>::iterator iter = m_runeMasteryLevel_MakableItem.find(skLevel);
	if( iter == m_runeMasteryLevel_MakableItem.end() )
		return RUNEITEM_ERROR;

	return iter->second.itemID;
}


int CRuneItemInfo::GetMakeSuccessPercentByLevel(int skLevel)
{
	if( skLevel < 1 || skLevel > 10 )
		return 0;

	return m_runeMastery_MakeSuccessPercent[skLevel - 1];
}


int CRuneItemInfo::GetUseSuccessPercentByLevel(int skLevel)
{
	if( skLevel < 1 || skLevel > 10 )
		return 0;

	return m_runeMastery_UseSuccessPercent[skLevel - 1];
}


int CRuneItemInfo::GetRuneItemMaxCount(int itemID)
{
	std::map<int,short>::iterator iter = m_runeItem_MaxCount.find(itemID);
	if( iter == m_runeItem_MaxCount.end() )
		return 0;

	return iter->second;
}


int CRuneItemInfo::GetMakableRuneItemRandomCount(int skLevel)
{
	if( skLevel < 1 || skLevel > 10 )
		return 0;

	return GetServerRandom(m_runeMastery_MakeMinCount[skLevel - 1], m_runeMastery_MakeMaxCount[skLevel - 1]);
}
