#include "MemorialDungeonConfig.h"
#include "shared/NLuaState.h"


/// singleton instance
CMemorialDungeonConfig*& CMemorialDungeonConfig::m_cpSelf = VTOR<CMemorialDungeonConfig*>(DetourFindFunction(EXEPATH(), "CMemorialDungeonConfig::m_cpSelf"));


namespace {
std::string MakeFormatString(const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf_s(Buffer, countof(Buffer), _TRUNCATE, in_pFmt, va);

	return Buffer;
}
}; // namespace


int MemorialDungeonConfigLuaGlueFunc_SetBaseConfig(lua_State* L)
{
	if( !lua_isnumber(L, -5) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -4) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 3rd is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -2) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 4th is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 5th is must number").c_str());
		return 2;
	}

	int nMaxBytes = (int)lua_tonumber(L, -5);
	int nEnterLimitMinute = (int)lua_tonumber(L, -4);
	int nSubscriptionMinimumDelaySecond = (int)lua_tonumber(L, -3);
	int nDatabaseLogOutput = (int)lua_tonumber(L, -2);
	int nOpen = (int)lua_tonumber(L, -1);

	if( !CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::SetBaseConfig(nMaxBytes, nEnterLimitMinute, nSubscriptionMinimumDelaySecond, nDatabaseLogOutput, nOpen) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int MemorialDungeonConfigLuaGlueFunc_RegisterMemorialDungeon(lua_State* L)
{
	if( !lua_isstring(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must string").c_str());
		return 2;
	}

	std::string szTitle = lua_tolstring(L, -1, NULL);

	if( !CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::RegisterMemorialDungeon(szTitle) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int MemorialDungeonConfigLuaGlueFunc_InsertMDMap(lua_State* L)
{
	if( !lua_isstring(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must string").c_str());
		return 2;
	}

	if( !lua_isstring(L, -2) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must string").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 3rd is must number").c_str());
		return 2;
	}


	std::string szIndex = lua_tolstring(L, -3, NULL);
	std::string szTitle = lua_tolstring(L, -2, NULL);
	int nMapType = (int)lua_tonumber(L, -1);

	if( !CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::InsertMDMap(szIndex, szTitle, nMapType) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int MemorialDungeonConfigLuaGlueFunc_InsertMDLiveTimeMinute(lua_State* L)
{
	if( !lua_isstring(L, -2) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must string").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must number").c_str());
		return 2;
	}

	std::string szIndex = lua_tolstring(L, -2, NULL);
	int nMinute = (int)lua_tonumber(L, -1);

	if( !CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::InsertMDLiveTimeMinute(szIndex, nMinute) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int MemorialDungeonConfigLuaGlueFunc_InsertMDEnterMap(lua_State* L)
{
	if( !lua_isstring(L, -4) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must string").c_str());
		return 2;
	}

	if( !lua_isstring(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must string").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -2) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 3rd is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 4th is must number").c_str());
		return 2;
	}

	std::string szIndex = lua_tolstring(L, -4, NULL);
	std::string szMapName = lua_tolstring(L, -3, NULL);
	int nXpos = (int)lua_tonumber(L, -2);
	int nYpos = (int)lua_tonumber(L, -1);

	if( !CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::InsertMDEnterMap(szIndex, szMapName, nXpos, nYpos) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int MemorialDungeonConfigLuaGlueFunc_InsertMDPlaceWithMap(lua_State* L)
{
	if( !lua_isstring(L, -2) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must string").c_str());
		return 2;
	}

	if( !lua_isstring(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must string").c_str());
		return 2;
	}

	std::string szIndex = lua_tolstring(L, -2, NULL);
	std::string szMapName = lua_tolstring(L, -1, NULL);

	if( !CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::InsertMDPlaceWithMap(szIndex, szMapName) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


CMemorialDungeonConfig::CMemorialDungeonConfig()
{
	m_bOK = true;
}


CMemorialDungeonConfig::~CMemorialDungeonConfig()
{
}


bool CMemorialDungeonConfig::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMemorialDungeonConfig();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMemorialDungeonConfig::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMemorialDungeonConfig::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMemorialDungeonConfig* CMemorialDungeonConfig::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMemorialDungeonConfig::isOK() const
{
	return m_bOK;
}


bool CMemorialDungeonConfig::Init()
{
	return this->CMemorialDungeonConfig::LoadTbl();
}



bool CMemorialDungeonConfig::LoadTbl()
{
	NLuaState LuaState;
	if( !LuaState.NLuaState::isOK() )
		return false;

	luaL_openlibs(LuaState);

	lua_pushcclosure(LuaState, &MemorialDungeonConfigLuaGlueFunc_SetBaseConfig, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "SetBaseConfig");
	lua_pushcclosure(LuaState, &MemorialDungeonConfigLuaGlueFunc_RegisterMemorialDungeon, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "RegisterMemorialDungeon");
	lua_pushcclosure(LuaState, &MemorialDungeonConfigLuaGlueFunc_InsertMDMap, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "InsertMDMap");
	lua_pushcclosure(LuaState, &MemorialDungeonConfigLuaGlueFunc_InsertMDLiveTimeMinute, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "InsertMDLiveTimeMinute");
	lua_pushcclosure(LuaState, &MemorialDungeonConfigLuaGlueFunc_InsertMDEnterMap, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "InsertMDEnterMap");
	lua_pushcclosure(LuaState, &MemorialDungeonConfigLuaGlueFunc_InsertMDPlaceWithMap, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "InsertMDPlaceWithMap");

	if( luaL_loadfile(LuaState, "MemorialDungeonConfig.lua") != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "CMemorialDungeonConfig", MB_OK);
		return false;
	}

	if( lua_pcall(LuaState, 0, 0, 0) )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "CMemorialDungeonConfig", MB_OK);
		return false;
	}

	lua_getfield(LuaState, LUA_GLOBALSINDEX, "main");
	if( lua_pcall(LuaState, 0, 2, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "CMemorialDungeonConfig", MB_OK);
		return false;
	}

	if( !lua_isstring(LuaState, -1) )
	{
		MessageBoxA(NULL, "second return value is not string...", "CMemorialDungeonConfig", MB_OK);
		return false;
	}

	if( !lua_toboolean(LuaState, -2) )
	{
		std::string msg = std::string("error found :") + lua_tolstring(LuaState, -1, NULL);
		MessageBoxA(NULL, msg.c_str(), "CMemorialDungeonConfig", MB_OK);
		return false;
	}

	return true;
}


std::pair<bool,CMemorialDungeonConfig::lcMDConfigData> CMemorialDungeonConfig::GetOnceMDObj(const std::string in_szIndex)
{
	if( in_szIndex == "" )
		return std::make_pair(false, lcMDConfigData());

	MDCONFIGOBJ::iterator iter = m_MDConfigInfo.find(in_szIndex);
	if( iter == m_MDConfigInfo.end() )
		return std::make_pair(false, lcMDConfigData());

	return std::make_pair(true, iter->second);
}


bool CMemorialDungeonConfig::SetBaseConfig(const int in_nMaxMemoryBytes, const int in_nEnterLimitMinute, const int in_nSubscriptionMinimumDelaySecond, const int in_nDatabaseLogOutput, const int in_nOpen)
{
	if( in_nMaxMemoryBytes <= 0 || in_nEnterLimitMinute <= 0 || in_nSubscriptionMinimumDelaySecond <= 0 || in_nDatabaseLogOutput <= 0 || in_nOpen <= 0 )
		return false;

	m_nMaxMemoryBytes = in_nMaxMemoryBytes;
	m_nEnterLimitMinute = in_nEnterLimitMinute;
	m_nSubscriptionMinimumDelaySecond = in_nSubscriptionMinimumDelaySecond;
	m_nDatabaseLogOutput = in_nDatabaseLogOutput;
	m_bOpen = ( in_nOpen > 0 );
	return true;
}


bool CMemorialDungeonConfig::RegisterMemorialDungeon(const std::string in_szTitle)
{
	if( in_szTitle == "" )
		return false;

	MDCONFIGOBJ::iterator iter = m_MDConfigInfo.find(in_szTitle);
	if( iter != m_MDConfigInfo.end() )
		return false;

	m_MDConfigInfo.insert(std::pair<const std::string,lcMDConfigData>(in_szTitle, lcMDConfigData(in_szTitle)));
	return true;
}


bool CMemorialDungeonConfig::InsertMDMap(const std::string in_szIndex, const std::string in_szMapName, const int in_nMapType)
{
	if( in_szIndex == "" || in_szMapName == "" || in_nMapType <= 0 )
		return false;

	MDCONFIGOBJ::iterator iter = m_MDConfigInfo.find(in_szIndex);
	if( iter == m_MDConfigInfo.end() )
		return false;

	iter->second.m_MapInfoObj.push_back(lcMDConfigData::MDMapInfo(in_szMapName, in_nMapType));
	return true;
}


bool CMemorialDungeonConfig::InsertMDLiveTimeMinute(const std::string in_szIndex, const int in_nMinute)
{
	if( in_szIndex == "" || in_nMinute <= 0 )
		return false;

	MDCONFIGOBJ::iterator iter = m_MDConfigInfo.find(in_szIndex);
	if( iter == m_MDConfigInfo.end() )
		return false;

	iter->second.m_nLiveTimeMinute = in_nMinute;
	return true;
}


bool CMemorialDungeonConfig::InsertMDEnterMap(const std::string in_szIndex, const std::string in_szMapName, const int in_nXpos, const int in_nYpos)
{
	if( in_szIndex == "" || in_szMapName == "" || in_nXpos <= 0 || in_nYpos <= 0 )
		return false;

	MDCONFIGOBJ::iterator iter = m_MDConfigInfo.find(in_szIndex);
	if( iter == m_MDConfigInfo.end() )
		return false;

	iter->second.m_lcEnterMapInfo.m_szMapName = in_szMapName;
	iter->second.m_lcEnterMapInfo.m_nXpos = in_nXpos;
	iter->second.m_lcEnterMapInfo.m_nYpos = in_nYpos;
	return true;
}


bool CMemorialDungeonConfig::InsertMDPlaceWithMap(const std::string in_szIndex, const std::string in_szMapName)
{
	if( in_szIndex == "" || in_szMapName == "" )
		return false;

	MDCONFIGOBJ::iterator iter = m_MDConfigInfo.find(in_szIndex);
	if( iter == m_MDConfigInfo.end() )
		return false;

	iter->second.m_szPlaceWithMap = in_szMapName;
	return true;
}
