#include "CZoneProcessLocalConfigMgr.h"
#include "shared/NLuaState.h"


/// singleton instance
CZoneProcessLocalConfigMgr*& CZoneProcessLocalConfigMgr::m_cpSelf = VTOR<CZoneProcessLocalConfigMgr*>(DetourFindFunction(EXEPATH(), "CZoneProcessLocalConfigMgr::m_cpSelf"));


namespace {
std::string MakeFormatString(const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf(Buffer, countof(Buffer), in_pFmt, va);

	return Buffer;
}
}; // namespace


CZoneProcessLocalConfigMgr::CZoneProcessLocalConfigMgr()
: 	m_ZSID(-1), m_bOK(false)
{
	m_bOK = true;
}


CZoneProcessLocalConfigMgr::~CZoneProcessLocalConfigMgr()
{
}


bool CZoneProcessLocalConfigMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CZoneProcessLocalConfigMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CZoneProcessLocalConfigMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CZoneProcessLocalConfigMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CZoneProcessLocalConfigMgr* CZoneProcessLocalConfigMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CZoneProcessLocalConfigMgr::isOK() const
{
	return m_bOK;
}


int ZoneProcessLocalConfigMgr_SetZsvrID(lua_State* L)
{
	if( lua_isnumber(L, -1) )
	{
		int ZSID = (int)lua_tonumber(L, -1);
		CZoneProcessLocalConfigMgr::GetObj()->CZoneProcessLocalConfigMgr::SetZSID(ZSID);

		lua_pushboolean(L, TRUE);
		lua_pushstring(L, MakeFormatString("good").c_str());
	}
	else
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("[SetZsvrID]argment is must number").c_str());
	}

	return 2;
}


bool CZoneProcessLocalConfigMgr::Init()
{
	NLuaState LuaState;
	if( !LuaState.NLuaState::isOK() )
		return false;

	luaL_openlibs(LuaState);

	lua_pushcclosure(LuaState, &ZoneProcessLocalConfigMgr_SetZsvrID, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "SetZsvrID");

	if( luaL_loadfile(LuaState, "ZoneProcess.Local.Config.lua") != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "CZoneProcessLocalConfigMgr", MB_OK);
		return false;
	}

	if( lua_pcall(LuaState, 0, 0, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "CZoneProcessLocalConfigMgr", MB_OK);
		return false;
	}

	lua_getfield(LuaState, LUA_GLOBALSINDEX, "main");

	if( lua_pcall(LuaState, 0, 2, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, NULL), "CZoneProcessLocalConfigMgr", MB_OK);
		return false;
	}

	if( !lua_isstring(LuaState, -1) )
	{
		MessageBoxA(NULL, "second return value is not string...", "CZoneProcessLocalConfigMgr", MB_OK);
		return false;
	}

	if( !lua_toboolean(LuaState, -2) )
	{
		std::string msg = std::string("error found unknown item :") + std::string(lua_tolstring(LuaState, -1, NULL));
		MessageBoxA(NULL, msg.c_str(), "CZoneProcessLocalConfigMgr", MB_OK);
		return false;
	}

	return true;
}


int CZoneProcessLocalConfigMgr::GetZSID()
{
	return m_ZSID;
}


void CZoneProcessLocalConfigMgr::SetZSID(const int ZSID)
{
	m_ZSID = ZSID;
}
