#include "PremiumServiceInfo.h"
#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/NLuaState.h"
#include "Common/NSyncObject.h"


/// singleton instance
CPremiumServiceInfo* CPremiumServiceInfo::m_cpSelf;


namespace {
std::string MakeFormatString(const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf_s(Buffer, sizeof(Buffer), _TRUNCATE, in_pFmt, va);

	return Buffer;
}
}; // namespace


int PremiumServiceInfoLuaGlueFunc_SetPremiumFlag(lua_State* L)
{
	if( !lua_isnumber(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1th is must number").c_str());
		return 2;
	}

	BOOL bPrmFlag = (BOOL)lua_tonumber(L, -1);
	CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::SetPremiumFlag(bPrmFlag);

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int PremiumServiceInfoLuaGlueFunc_SetGravityPublicIP(lua_State* L)
{
	if( !lua_isstring(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1th is must string").c_str());
		return 2;
	}

	std::string szGravityPublicIP = lua_tolstring(L, -1, NULL);
	CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::SetGravityPublicIP(szGravityPublicIP.c_str());

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int PremiumServiceInfoLuaGlueFunc_SetPCBangFlag(lua_State* L)
{
	if( !lua_isnumber(L, -1) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1th is must number").c_str());
		return 2;
	}

	BOOL bPCBangPrmFlag = (BOOL)lua_tonumber(L, -1);
	CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::SetPCBangFlag(bPCBangPrmFlag);

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int PremiumServiceInfoLuaGlueFunc_SetNonePremiumSvcInfo(lua_State* L)
{
	if( !lua_isnumber(L, -4) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must number").c_str());
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

	const float fExp = (float)lua_tonumber(L, -4);
	const float fDeath = (float)lua_tonumber(L, -3);
	const float fDrop = (float)lua_tonumber(L, -2);
	const int fMaxStoreCnt = (int)lua_tonumber(L, -1);

	if( CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::SetNonePremiumSvcInfo(fExp, fDeath, fDrop, (float)fMaxStoreCnt) != true )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int PremiumServiceInfoLuaGlueFunc_SetCommonPremiumSvcInfo(lua_State* L)
{
	if( !lua_isnumber(L, -4) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must number").c_str());
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

	const float fExp = (float)lua_tonumber(L, -4);
	const float fDeath = (float)lua_tonumber(L, -3);
	const float fDrop = (float)lua_tonumber(L, -2);
	const int nMaxStoreCnt = (int)lua_tonumber(L, -1);

	CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::SetCommonPremiumSvcInfo(fExp, fDeath, fDrop, nMaxStoreCnt);

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int PremiumServiceInfoLuaGlueFunc_SetPCBangGradeInfo(lua_State* L)
{
	if( !lua_isnumber(L, -4) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 1st is must number").c_str());
		return 2;
	}

	if( !lua_isnumber(L, -3) )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("argument 2nd is must number").c_str());
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

	const int in_nPCBangGrade = (int)lua_tonumber(L, -4);
	const float fExp = (float)lua_tonumber(L, -3);
	const float fDeath = (float)lua_tonumber(L, -2);
	const float fDrop = (float)lua_tonumber(L, -1);

	if( CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::SetPCBangGradeInfo(in_nPCBangGrade, fExp, fDeath, fDrop) != true )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


int PremiumServiceInfoLuaGlueFunc_SetPremiumSvcInfo(lua_State* L)
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


	const int nGrade = (int)lua_tonumber(L, -5);
	const float fExp = (float)lua_tonumber(L, -4);
	const float fDeath = (float)lua_tonumber(L, -3);
	const float fDrop = (float)lua_tonumber(L, -2);
	const int nMaxStoreCnt = (int)lua_tonumber(L, -1);

	if( CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::SetPremiumSvcInfo(nGrade, fExp, fDeath, fDrop, nMaxStoreCnt) != true )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, MakeFormatString("insert failed").c_str());
		return 2;
	}

	lua_pushboolean(L, TRUE);
	lua_pushstring(L, MakeFormatString("good").c_str());
	return 2;
}


CPremiumServiceInfo::CPremiumServiceInfo()
{
	m_bOK = false;
	InitializeCriticalSection(&m_cs);
	m_bOK = true;
}


bool CPremiumServiceInfo::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new(std::nothrow) CPremiumServiceInfo();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
		return false;

	return true;
}


CPremiumServiceInfo* CPremiumServiceInfo::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CPremiumServiceInfo::isOK() const
{
	return m_bOK;
}


bool CPremiumServiceInfo::Init()
{
	NLuaState lua;
	if( !lua.isOK() )
		return false;

	luaL_openlibs(lua);
	lua_pushcclosure(lua, &PremiumServiceInfoLuaGlueFunc_SetPremiumFlag, 0);
	lua_setfield(lua, LUA_GLOBALSINDEX, "SetPremiumFlag");
	lua_pushcclosure(lua, &PremiumServiceInfoLuaGlueFunc_SetGravityPublicIP, 0);
	lua_setfield(lua, LUA_GLOBALSINDEX, "SetGravityPublicIP");
	lua_pushcclosure(lua, &PremiumServiceInfoLuaGlueFunc_SetNonePremiumSvcInfo, 0);
	lua_setfield(lua, LUA_GLOBALSINDEX, "SetNonePremiumSvcInfo");
	lua_pushcclosure(lua, &PremiumServiceInfoLuaGlueFunc_SetCommonPremiumSvcInfo, 0);
	lua_setfield(lua, LUA_GLOBALSINDEX, "SetCommonPremiumSvcInfo");
	lua_pushcclosure(lua, &PremiumServiceInfoLuaGlueFunc_SetPremiumSvcInfo, 0);
	lua_setfield(lua, LUA_GLOBALSINDEX, "SetPremiumSvcInfo");
	lua_pushcclosure(lua, &PremiumServiceInfoLuaGlueFunc_SetPCBangFlag, 0);
	lua_setfield(lua, LUA_GLOBALSINDEX, "SetPCBangFlag");
	lua_pushcclosure(lua, &PremiumServiceInfoLuaGlueFunc_SetPCBangGradeInfo, 0);
	lua_setfield(lua, LUA_GLOBALSINDEX, "SetPCBangGradeInfo");

	if( luaL_loadfile(lua, "PremiumServiceInfo.lua") != 0 )
	{
		MessageBoxA(NULL, lua_tostring(lua, -1), "CPremiumServiceInfo", MB_OK);
		return false;
	}

	if( lua_pcall(lua, 0, 0, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tostring(lua, -1), "CPremiumServiceInfo", MB_OK);
		return false;
	}

	lua_getfield(lua, LUA_GLOBALSINDEX, "main");

	if( lua_pcall(lua, 0, 2, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tostring(lua, -1), "CPremiumServiceInfo", MB_OK);
		return false;
	}

	if( lua_isstring(lua, -1) == 0 )
	{
		MessageBoxA(NULL, "second return value is not string...", "CPremiumServiceInfo", MB_OK);
		return false;
	}

	if( lua_toboolean(lua, -2) == 0 )
	{
		std::string message = std::string("error found :") + std::string(lua_tostring(lua, -1));
		MessageBoxA(NULL, message.c_str(), "CPremiumServiceInfo", 0);
		return false;
	}

	return true;
}


bool CPremiumServiceInfo::SetPremiumFlag(const BOOL bPrmFlag)
{
	m_bPrmFlag = ( bPrmFlag ) ? true : false;
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "PremiumService : Personal_Premium (%d)", m_bPrmFlag);
	return true;
}


bool CPremiumServiceInfo::SetPCBangFlag(const BOOL bPCBangPrmFlag)
{
	m_bPCBangPrmFlag = ( bPCBangPrmFlag ) ? true : false;
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "PCBang Premium : (%d)", m_bPCBangPrmFlag);
	return true;
}


bool CPremiumServiceInfo::SetGravityPublicIP(const char* szGravityPublicIP)
{
	m_dwGravityPublicIP = CNetwork::GetObj()->CNetwork::GetDWORDIP(szGravityPublicIP);
	return true;
}


bool CPremiumServiceInfo::SetNonePremiumSvcInfo(const float in_fExp, const float in_fDeath, const float in_fDrop, const float in_fMaxStoreCnt)
{
	m_stNonePrmInfo = new PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO(in_fExp, in_fDeath, in_fDrop, static_cast<int>(in_fMaxStoreCnt));
	return true;
}


bool CPremiumServiceInfo::SetCommonPremiumSvcInfo(const float in_fExp, const float in_fDeath, const float in_fDrop, const int in_fMaxStoreCnt)
{
	m_stCommonPrmInfo = new PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO(in_fExp, in_fDeath, in_fDrop, in_fMaxStoreCnt);
	return true;
}


bool CPremiumServiceInfo::SetPremiumSvcInfo(const int in_nGrade, const float in_fExp, const float in_fDeath, const float in_fDrop, const int in_nMaxStoreCnt)
{
	std::map<int,PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO>::const_iterator it = m_mapPrmInfo.find(in_nGrade);
	if( it != m_mapPrmInfo.end() )
		return false; // already set.

	m_mapPrmInfo.insert(std::pair<int,PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO>(in_nGrade, PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO(in_fExp, in_fDeath, in_fDrop, in_nMaxStoreCnt)));
	return true;
}


bool CPremiumServiceInfo::SetPCBangGradeInfo(const int in_nPCBangGrade, const float in_fExp, const float in_fDeath, const float in_fDrop)
{
	std::map<int,PERSONAL_PREMIUM_INFO::PCBANG_PREMIUM_INFO>::const_iterator it = m_mapPCBangInfo.find(in_nPCBangGrade);
	if( it != m_mapPCBangInfo.end() )
		return false; // already set.

	m_mapPCBangInfo.insert(std::pair<int,PERSONAL_PREMIUM_INFO::PCBANG_PREMIUM_INFO>(in_nPCBangGrade, PERSONAL_PREMIUM_INFO::PCBANG_PREMIUM_INFO(in_fExp, in_fDeath, in_fDrop)));
	return true;
}


bool CPremiumServiceInfo::GetInfo(const int in_nGrade, PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO* out_pInfo)
{
	NSyncObject sync(m_cs);

	std::map<int,PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO>::const_iterator it = m_mapPrmInfo.find(in_nGrade);
	if( it == m_mapPrmInfo.end() )
		return false;

	if( m_bPrmFlag == true )
	{// premium
		out_pInfo->fExp        += it->second.fExp;
		out_pInfo->fDeath      += it->second.fDeath;
		out_pInfo->fDrop       += it->second.fDrop;
		out_pInfo->nMaxStoreCnt = it->second.nMaxStoreCnt;
	}
	else
	if( in_nGrade != 0 )
	{// common
		out_pInfo->fExp        += m_stCommonPrmInfo->fExp;
		out_pInfo->fDeath      += m_stCommonPrmInfo->fDeath;
		out_pInfo->fDrop       += m_stCommonPrmInfo->fDrop;
		out_pInfo->nMaxStoreCnt = m_stCommonPrmInfo->nMaxStoreCnt;
	}
	else
	{// none
		out_pInfo->fExp        += m_stNonePrmInfo->fExp;
		out_pInfo->fDeath      += m_stNonePrmInfo->fDeath;
		out_pInfo->fDrop       += m_stNonePrmInfo->fDrop;
		out_pInfo->nMaxStoreCnt = m_stNonePrmInfo->nMaxStoreCnt;
	}

	return true;
}
