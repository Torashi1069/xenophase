#include "MobTombInfo.h"
#include "shared/NLuaState.h"


/// singleton instance
CScriptMobTombInfo*& CScriptMobTombInfo::m_cpSelf = VTOR<CScriptMobTombInfo*>(DetourFindFunction(EXEPATH(), "CScriptMobTombInfo::m_cpSelf"));


static int LoadMobTomb(lua_State* L)
{
	if( !lua_isstring(L, -4) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argment 1st is must string").c_str());
		return 2;
	}

	if( !lua_isstring(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argment 2st is must string").c_str());
		return 2;
	}

	if( !lua_isstring(L, -2) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argment 3st is must string").c_str());
		return 2;
	}

	if( !lua_isstring(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argment 4nd is must string").c_str());
		return 2;
	}

	CScriptMobTombInfo::MobTombInfo scriptMobtombInfo;
	scriptMobtombInfo.DialogMsg[2] = lua_tolstring(L, -1, NULL); lua_settop(L, -2);
	scriptMobtombInfo.DialogMsg[1] = lua_tolstring(L, -1, NULL); lua_settop(L, -2);
	scriptMobtombInfo.DialogMsg[0] = lua_tolstring(L, -1, NULL); lua_settop(L, -2);
	scriptMobtombInfo.NpcName      = lua_tolstring(L, -1, NULL); lua_settop(L, -2);
	CScriptMobTombInfo::GetObj()->CScriptMobTombInfo::SetMobTombInfo(scriptMobtombInfo);

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


CScriptMobTombInfo::CScriptMobTombInfo()
: m_bCreateInstance(false), m_FileName("MobTomb.lua")
{
	m_bCreateInstance = true;
}


CScriptMobTombInfo::~CScriptMobTombInfo()
{
	m_bCreateInstance = false;
}


bool CScriptMobTombInfo::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CScriptMobTombInfo();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CScriptMobTombInfo::IsCreateInstance() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CScriptMobTombInfo::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CScriptMobTombInfo* CScriptMobTombInfo::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CScriptMobTombInfo::IsCreateInstance()
{
	return m_bCreateInstance;
}


bool CScriptMobTombInfo::LoadLuaFIle()
{
	NLuaState LuaState;
	if( !LuaState.NLuaState::isOK() )
		return false;

	luaL_openlibs(LuaState);
	lua_pushcclosure(LuaState, &LoadMobTomb, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "SetMobTombInfo");

	if( luaL_loadfile(LuaState, m_FileName.c_str()) )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "LoadMobTombFile()", MB_OK);
		return false;
	}

	if( lua_pcall(LuaState, 0, 0, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "LoadMobTombFile()", MB_OK);
		return false;
	}

	lua_getfield(LuaState, LUA_GLOBALSINDEX, "main");
	if( lua_pcall(LuaState, 0, 2, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "LoadMobTombFile()", MB_OK);
		return false;
	}

	if( !lua_isstring(LuaState, -1) )
	{
		MessageBoxA(NULL, "second return value is not string...", "LoadMobTombFile()", MB_OK);
		return false;
	}

	if( !lua_toboolean(LuaState, -2) )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "LoadMobTombFile()", MB_OK);
		return false;
	}

	return true;
}


const CScriptMobTombInfo::MobTombInfo& CScriptMobTombInfo::GetMobTombInfo()
{
	return m_MobTombInfo;
}


void CScriptMobTombInfo::SetMobTombInfo(const CScriptMobTombInfo::MobTombInfo& info)
{
	m_MobTombInfo = info;
}
