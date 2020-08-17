#include "MServerLog.h"
#include "ServerExpInfoMgr.h"
#include "shared/NLuaState.h"


/// singleton instance
CServerExpInfoMgr*& CServerExpInfoMgr::m_cpSelf = VTOR<CServerExpInfoMgr*>(DetourFindFunction(EXEPATH(), "CServerExpInfoMgr::m_cpSelf"));


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


int __cdecl ServerExpInfoMgrLuaGlueFunc_SetRestrictEXPInfo(lua_State* L)
{
	if( !lua_isnumber(L, -6) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -5) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -4) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 3rd is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 4th is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -2) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 5th is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 6th is must number").c_str());
		return 2;
	}

	int nMinExp = (int)lua_tonumber(L, -6);
	int nMaxExp = (int)lua_tonumber(L, -5);
	int nMinDeath = (int)lua_tonumber(L, -4);
	int nMaxDeath = (int)lua_tonumber(L, -3);
	int nMinDrop = (int)lua_tonumber(L, -2);
	int nMaxDrop = (int)lua_tonumber(L, -1);
	if( CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::SetRestrictEXPInfo(nMinExp, nMaxExp, nMinDeath, nMaxDeath, nMinDrop, nMaxDrop) != true )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int ServerExpInfoMgrLuaGlueFunc_SetExpIAuthenticate(lua_State* L)
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

	std::string strID = lua_tolstring(L, -2, NULL);
	std::string strPW = lua_tolstring(L, -1, NULL);
	if( CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::SetExpIAuthenticate(strID, strPW) != true )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int ServerExpInfoMgrLuaGlueFunc_SetServerEXPInfo(lua_State* L)
{
	if( !lua_isnumber(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -2) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 3st is must number").c_str());
		return 2;
	}

	int nExp = (int)lua_tonumber(L, -3);
	int nDeath = (int)lua_tonumber(L, -2);
	int nDrop = (int)lua_tonumber(L, -1);
	if( CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::SetServerEXPInfo(nExp, nDeath, nDrop) != true )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


CServerExpInfoMgr::CServerExpInfoMgr()
: m_strID(""), m_strPW("")
{
	m_bOK = true;
}


CServerExpInfoMgr::~CServerExpInfoMgr()
{
}


bool CServerExpInfoMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CServerExpInfoMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CServerExpInfoMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CServerExpInfoMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CServerExpInfoMgr* CServerExpInfoMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CServerExpInfoMgr::isOK() const
{
	return m_bOK;
}


int CServerExpInfoMgr::GetExp()
{
	return m_Exp.m_Value;
}


int CServerExpInfoMgr::GetDeath()
{
	return m_Death.m_Value;
}


int CServerExpInfoMgr::GetDrop()
{
	return m_Drop.m_Value;
}


bool CServerExpInfoMgr::SetExpIAuthenticate(const std::string in_strID, const std::string in_strPW)
{
	if( in_strID.size() == 0 || in_strPW.size() == 0 )
	{
		MessageBoxA(NULL, "경험치 수정 권한 인증 정보가 잘못되었습니다.", "초기설정오류", MB_OK);
		return false;
	}

	m_strID = in_strID;
	m_strPW = in_strPW;

	return true;
}


bool CServerExpInfoMgr::IsAuthenticate(const std::string in_ID, const std::string in_Pwd)
{
	return ( strcmp(m_strID.c_str(), in_ID.c_str()) == 0 && strcmp(m_strPW.c_str(), in_Pwd.c_str()) == 0 );
}


bool CServerExpInfoMgr::Init()
{
	return this->CServerExpInfoMgr::LoadTbl();
}


bool CServerExpInfoMgr::LoadTbl()
{
	NLuaState LuaState;
	if( !LuaState.NLuaState::isOK() )
		return false;

	luaL_openlibs(LuaState);
	lua_pushcclosure(LuaState, &ServerExpInfoMgrLuaGlueFunc_SetExpIAuthenticate, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "SetExpIAuthenticate");
	lua_pushcclosure(LuaState, &ServerExpInfoMgrLuaGlueFunc_SetServerEXPInfo, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "SetServerEXPInfo");
	lua_pushcclosure(LuaState, &ServerExpInfoMgrLuaGlueFunc_SetRestrictEXPInfo, 0);
	lua_setfield(LuaState, LUA_GLOBALSINDEX, "SetRestrictEXPInfo");

	if( luaL_loadfile(LuaState, "ServerExpInfoMgr.lua") != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, 0), "CServerExpInfoMgr", MB_OK);
		return false;
	}

	if( lua_pcall(LuaState, 0, 0, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, 0), "CServerExpInfoMgr", MB_OK);
		return false;
	}

	lua_getfield(LuaState, LUA_GLOBALSINDEX, "main");

	if( lua_pcall(LuaState, 0, 2, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(LuaState, -1, 0), "CServerExpInfoMgr", MB_OK);
		return false;
	}

	if( lua_isstring(LuaState, -1) == 0 )
	{
		MessageBoxA(NULL, "second return value is not string...", "CServerExpInfoMgr", MB_OK);
		return false;
	}

	if( lua_toboolean(LuaState, -2) == 0 )
	{
		std::string msg;
		msg += "error found :";
		msg += lua_tostring(LuaState, -1);

		MessageBoxA(NULL, msg.c_str(), "CServerExpInfoMgr", MB_OK);
		return false;
	}

	return true;
}


bool CServerExpInfoMgr::SetServerEXPInfo(const int in_nExp, const int in_nDeath, const int in_nDrop)
{
	if( in_nExp < 0 || in_nExp > 200 )
	{
		CMServerLog::GetObj()->CMServerLog::LogFmt("[EDD] exp restrict : min(%d), max(%d), cur(%d)", m_Exp.m_Min, m_Exp.m_Max, in_nExp);
		return false;
	}

	if( in_nDeath < -100 || in_nDeath > 0 )
	{
		CMServerLog::GetObj()->CMServerLog::LogFmt(__FILE__, __LINE__, "[EDD] death restrict : min(%d), max(%d), cur(%d)", m_Death.m_Min, m_Death.m_Max, in_nDeath); //FIXME: parameter mismatch
		return false;
	}

	if( in_nDrop < 0 || in_nDrop > 200 )
	{
		CMServerLog::GetObj()->CMServerLog::LogFmt(__FILE__, __LINE__, "[EDD] drop restrict : min(%d), max(%d), cur(%d)", m_Drop.m_Min, m_Drop.m_Max, in_nDrop); //FIXME: parameter mismatch
		return false;
	}

	m_Exp.m_Value = in_nExp;
	m_Death.m_Value = in_nDeath;
	m_Drop.m_Value = in_nDrop;

	return true;
}


bool CServerExpInfoMgr::SetRestrictEXPInfo(const int in_nMinExp, const int in_nMaxExp, const int in_nMinDeath, const int in_nMaxDeath, const int in_nMinDrop, const int in_nMaxDrop)
{
	m_Exp.m_Min = in_nMinExp;
	m_Exp.m_Max = in_nMaxExp;
	m_Death.m_Min = in_nMinDeath;
	m_Death.m_Max = in_nMaxDeath;
	m_Drop.m_Min = in_nMinDrop;
	m_Drop.m_Max = in_nMaxDrop;

	return true;
}


void CServerExpInfoMgr::CreateServerEXPFile(const int in_nExp, const int in_nDeath, const int in_nDrop)
{
	FILE* fp;
	fopen_s(&fp, "ServerExpInfo.lua", "w");
	if( fp == NULL )
		return;

	fprintf_s(fp, "SERVER_EXP_INFO = \n");
	fprintf_s(fp, "{\n");
	fprintf_s(fp, "\tEXP = %d, \n", in_nExp);
	fprintf_s(fp, "\tDEATH = %d, \n", in_nDeath);
	fprintf_s(fp, "\tDROP = %d, \n", in_nDrop);
	fprintf_s(fp, "}\n");

	fclose(fp);
}
