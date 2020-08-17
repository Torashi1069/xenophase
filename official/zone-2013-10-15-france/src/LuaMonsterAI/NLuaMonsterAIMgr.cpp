#include "CharacterMgr.h"
#include "NpcMob.h"
#include "LuaMonsterAI/NLuaMonsterAIGlueFunc.h"
#include "LuaMonsterAI/NLuaMonsterAIMgr.h"
#include "shared/NCriticalErrorLog.h"


/// singleton instance
NLuaMonsterAIMgr*& NLuaMonsterAIMgr::m_cpSelf = VTOR<NLuaMonsterAIMgr*>(DetourFindFunction(EXEPATH(), "NLuaMonsterAIMgr::m_cpSelf"));


/// statics
const NLuaMonsterAIMgr::tagLuaGlueFunc NLuaMonsterAIMgr::m_LuaGlueFuncTable[] = {
	{ LuaGlueFunc_Skill,          "Skill"          },
	{ LuaGlueFunc_IsRechargeTime, "IsRechargeTime" },
	{ LuaGlueFunc_Attack,         "Attack"         },
	{ LuaGlueFunc_Trace,          "Trace"          },
	{ LuaGlueFunc_SummaryUpdate,  "SummaryUpdate"  },
	{ LuaGlueFunc_GetAttackRange, "GetAttackRange" },
	{ LuaGlueFunc_Move,           "move"           },
	{ LuaGlueFunc_GetCurPos,      "getcurpos"      },
	{ LuaGlueFunc_Revival,        "revival"        },
	{ LuaGlueFunc_GetAsyncMsg,    "GetAsyncMsg"    },
	{ LuaGlueFunc_GetNeighborNum, "GetNeighborNum" },
	{ LuaGlueFunc_timeGetTime,    "GetNeighborNum" },
	{ LuaGlueFunc_PutMob,         "putmob"         },
	{ LuaGlueFunc_DebugMsg,       "DebugMsg"       },
	{ LuaGlueFunc_GetObjects,     "GetObjects"     },
	{ LuaGlueFunc_GetV,           "GetV"           },
	{ LuaGlueFunc_Chat,           "Chat"           },
	{ LuaGlueFunc_Emotion,        "Emotion"        },
	{ LuaGlueFunc_Teleport,       "Teleport"       },
	{ LuaGlueFunc_IsTarget,       "IsTarget"       },
	{ LuaGlueFunc_GetOwnerAID,    "GetOwnerAID"    },
	{ LuaGlueFunc_IsServiceMap,   "IsServiceMap"   },
	{ NULL,                       NULL             },
};


NLuaMonsterAIMgr::NLuaMonsterAIMgr()
: m_LuaState(), m_AppContainer(), m_bOK(false)
{
	if( this->NLuaMonsterAIMgr::Create() )
		m_bOK = true;
}


NLuaMonsterAIMgr::~NLuaMonsterAIMgr()
{
	this->NLuaMonsterAIMgr::Destroy();
}


NLuaMonsterAI* NLuaMonsterAIMgr::GetAppPtr(const int in_SvrScriptAppID) const
{
	std::map<int,NLuaMonsterAI*>::const_iterator iter = m_AppContainer.find(in_SvrScriptAppID);
	if( iter == m_AppContainer.end() )
		return NULL;

	return iter->second;
}


std::pair<bool,std::string> NLuaMonsterAIMgr::Init()
{
	if( luaL_loadfile(m_LuaState, "monster ai initialze.lua") != 0 )
		return std::pair<bool,std::string>(false, lua_tolstring(m_LuaState, -1, NULL));

	if( lua_pcall(m_LuaState, 0, 0, 0) != 0 )
		return std::pair<bool,std::string>(false, lua_tolstring(m_LuaState, -1, NULL));

	const char* const buff = "setmetatable( _G,{ __newindex = function( t, k, v ) error( \"global variable access denny\", 2 ) end })";
	if( luaL_loadbuffer(m_LuaState, buff, strlen(buff), "GVarProtectCmd") != 0 )
		return std::pair<bool,std::string>(false, lua_tolstring(m_LuaState, -1, NULL));

	if( lua_pcall(m_LuaState, 0, 0, 0) != 0 )
		return std::pair<bool,std::string>(false, lua_tolstring(m_LuaState, -1, NULL));

	lua_getfield(m_LuaState, LUA_GLOBALSINDEX, "main");

	if( lua_type(m_LuaState, -1) != LUA_TFUNCTION )
		return std::pair<bool,std::string>(false, "can't find main func");

	int ret = lua_resume(m_LuaState, 0);
	if( ret != 0 )
	{
		if( ret != LUA_YIELD )
			return std::pair<bool,std::string>(false, lua_tolstring(m_LuaState, -1, NULL));

		for( ; ; )
		{
			int ret = lua_resume(m_LuaState, lua_gettop(m_LuaState));
			if( ret == 0 )
				break;
			if( ret != LUA_YIELD )
				return std::pair<bool,std::string>(false, lua_tolstring(m_LuaState, -1, NULL));
		}
	}

	if( luaL_loadbuffer(m_LuaState, "main=nil", strlen("main=nil"), "main func remove") )
		return std::pair<bool,std::string>(false, lua_tolstring(m_LuaState, -1, NULL));

	if( lua_pcall(m_LuaState, 0, 0, 0) != 0 )
		return std::pair<bool,std::string>(false, lua_tolstring(m_LuaState, -1, NULL));

	return std::pair<bool,std::string>(true, "");
}


bool NLuaMonsterAIMgr::Create()
{
	if( !m_LuaState.NLuaState::isOK() )
		return false;
	
	luaL_openlibs(m_LuaState);

	lua_createtable(m_LuaState, 0, 0);

	if( lua_type(m_LuaState, -1) != LUA_TTABLE )
		return false;

	for( int idx = 0; m_LuaGlueFuncTable[idx].func != NULL; ++idx )
	{
		lua_pushstring(m_LuaState, m_LuaGlueFuncTable[idx].name);
		lua_pushcclosure(m_LuaState, m_LuaGlueFuncTable[idx].func, 0);
		lua_settable(m_LuaState, -3);
	}

	lua_setfield(m_LuaState, LUA_GLOBALSINDEX, "app");

	const char* const buff = "setmetatable( app,{ __newindex = function( t, k, v ) error( \"global variable access denny\", 2 ) end })";
	if( luaL_loadbuffer(m_LuaState, buff, strlen(buff), 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(m_LuaState, -1, NULL), "SvrScriptAppMgr", MB_OK);
		return false;
	}

	if( lua_pcall(m_LuaState, 0, 0, 0) != 0 )
	{
		MessageBoxA(NULL, lua_tolstring(m_LuaState, -1, NULL), "SvrScriptAppMgr", MB_OK);
		return false;
	}

	return true;
}


void NLuaMonsterAIMgr::Destroy()
{
	while( !m_AppContainer.empty() )
	{
		NLuaMonsterAI* cpApp = m_AppContainer.begin()->second;
		this->NLuaMonsterAIMgr::DestroyApp(cpApp->NLuaMonsterAI::GetID());
	}
}


bool NLuaMonsterAIMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) NLuaMonsterAIMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->NLuaMonsterAIMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NLuaMonsterAIMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


NLuaMonsterAIMgr* NLuaMonsterAIMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool NLuaMonsterAIMgr::isOK() const
{
	return m_bOK;
}


NLuaState& NLuaMonsterAIMgr::GetLuaState()
{
	return m_LuaState;
}


int NLuaMonsterAIMgr::GetNewAppID()
{
	static int AppIDCnt = 1;
	return AppIDCnt++;
}


void NLuaMonsterAIMgr::AppResume(NLuaMonsterAI* in_cpApp, const int in_NArg)
{
	lua_State* L = in_cpApp->NLuaMonsterAI::GetStatePtr();

	int ret = lua_resume(L, in_NArg);
	if( ret == 0 )
	{
		in_cpApp->m_ProcFuncStep.NLuaMonsterAI::NStep::Set(NLuaMonsterAI::PROCESSFUNC_STEP_EXIT);
	}
	else
	if( ret == LUA_YIELD )
	{
		in_cpApp->m_ProcFuncStep.NLuaMonsterAI::NStep::Set(NLuaMonsterAI::PROCESSFUNC_STEP_EXEC);
	}
	else
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%d - %s", ret, lua_tolstring(L, -1, NULL));
		in_cpApp->m_ProcFuncStep.NLuaMonsterAI::NStep::Set(NLuaMonsterAI::PROCESSFUNC_STEP_ERROR);
	}

}


void NLuaMonsterAIMgr::Process()
{
	std::vector<NLuaMonsterAI*> ErrorAppList;

	for( APP_CONTAINER_ITER iter = m_AppContainer.begin(); iter != m_AppContainer.end(); ++iter )
	{
		NLuaMonsterAI* cpApp = iter->second;

		NLuaMonsterAI::enumProcessFuncStep step = cpApp->m_ProcFuncStep.NLuaMonsterAI::NStep::Get();
		if( step == NLuaMonsterAI::PROCESSFUNC_STEP_NONE )
		{
			lua_State* L = cpApp->NLuaMonsterAI::GetStatePtr();
			int StackPos = lua_gettop(L);

			lua_getfield(L, LUA_GLOBALSINDEX, cpApp->m_Name.c_str());
			if( lua_type(L, -1) != LUA_TTABLE )
			{
				lua_settop(L, StackPos);
				continue;
			}

			lua_pushstring(L, "main");

			lua_gettable(L, -2);
			if( lua_type(L, -1) != LUA_TFUNCTION )
			{
				lua_settop(L, StackPos);
				continue;
			}

			lua_pushinteger(L, cpApp->NLuaMonsterAI::GetID());
			lua_pushinteger(L, cpApp->NLuaMonsterAI::GetAID());
			lua_createtable(L, 0, 0);
			this->NLuaMonsterAIMgr::AppResume(cpApp, 3);
		}
		else
		if( step == NLuaMonsterAI::PROCESSFUNC_STEP_EXEC )
		{
			lua_State* L = cpApp->NLuaMonsterAI::GetStatePtr();
			this->NLuaMonsterAIMgr::AppResume(cpApp, lua_gettop(L));
		}
		else
		if( step == NLuaMonsterAI::PROCESSFUNC_STEP_EXIT || step == NLuaMonsterAI::PROCESSFUNC_STEP_ERROR )
		{
			ErrorAppList.push_back(cpApp);
		}
	}

	DWORD CurTM = timeGetTime();

	for( std::vector<NLuaMonsterAI*>::iterator iter = ErrorAppList.begin(); iter != ErrorAppList.end(); ++iter )
	{
		NLuaMonsterAI* cpApp = *iter;

		NLuaMonsterAI::enumProcessFuncStep step = cpApp->m_ProcFuncStep.NLuaMonsterAI::NStep::Get();
		if( step != NLuaMonsterAI::PROCESSFUNC_STEP_EXIT && step != NLuaMonsterAI::PROCESSFUNC_STEP_ERROR )
			continue;

		if( CurTM < cpApp->m_ProcFuncStep.NLuaMonsterAI::NStep::GetTime() + 10000 )
			continue;

		cpApp->m_ProcFuncStep.NLuaMonsterAI::NStep::Set(step);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[Monster LuaAI] 오류발생 AID:%d AIName=%s", cpApp->NLuaMonsterAI::GetAID(), cpApp->m_Name.c_str());

		CNpcMob* npcMob = (CNpcMob*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(cpApp->NLuaMonsterAI::GetAID(), NPC_MOB_TYPE);
		if( npcMob == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[Monster LuaAI] 연결된 몬스터를 찾지 못했습니다");
			continue;
		}

		if( npcMob->CNpcMob::GetSvrScriptAppID() != cpApp->NLuaMonsterAI::GetID() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[Monster LuaAI] AppID값이 일치하지 않습니다");
			continue;
		}

		int AppID = this->NLuaMonsterAIMgr::CreateApp(cpApp->NLuaMonsterAI::GetAID(), cpApp->m_Name.c_str(), false);
		if( AppID == 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[Monster LuaAI] 새로운 AI생성 실패");
			continue;
		}

		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[Monster LuaAI] 새로운 AI를 만들어서 할당합니다.");
		npcMob->CNPC::SetAccountID(AppID); //FIXME: possible mistake, using AppID as AID
		this->NLuaMonsterAIMgr::DestroyApp(cpApp->NLuaMonsterAI::GetID());
	}
}


int NLuaMonsterAIMgr::CreateApp(unsigned long in_AID, const std::string in_Name, const bool in_bForceProcessing)
{
	NLuaMonsterAI* cpApp = new(std::nothrow) NLuaMonsterAI(this->NLuaMonsterAIMgr::GetNewAppID(), in_AID, in_bForceProcessing);
	if( cpApp == NULL )
		return 0;

	std::pair<APP_CONTAINER_ITER,bool> insertRet = m_AppContainer.insert(std::pair<const int,NLuaMonsterAI*>(cpApp->NLuaMonsterAI::GetID(), cpApp));
	if( insertRet.second != true )
	{
		delete cpApp;
		return 0;
	}

	int StackTop = lua_gettop(m_LuaState);

	NLuaThread* pThread = new(std::nothrow) NLuaThread(m_LuaState);
	if( pThread == NULL || pThread->NLuaThread::isOK() != true )
	{
		lua_settop(m_LuaState, StackTop);
		m_AppContainer.erase(insertRet.first);
		delete cpApp;
		return 0;
	}

	int ref = luaL_ref(m_LuaState, LUA_REGISTRYINDEX);
	cpApp->NLuaMonsterAI::Init(in_Name, pThread, ref);
	return cpApp->NLuaMonsterAI::GetID();
}


void NLuaMonsterAIMgr::DestroyApp(const int in_AppID)
{
	APP_CONTAINER_ITER iter = m_AppContainer.find(in_AppID);
	if( iter == m_AppContainer.end() )
		return;

	NLuaMonsterAI* cpApp = iter->second;
	if( cpApp->NLuaMonsterAI::GetRef() != -1 )
		luaL_unref(m_LuaState, LUA_REGISTRYINDEX, cpApp->NLuaMonsterAI::GetRef());
	delete cpApp;
	m_AppContainer.erase(iter);
}


int NLuaMonsterAIMgr::GetUsedMemoryBytes()
{
	return (lua_gc(m_LuaState, LUA_GCCOUNT, 0) << 10) + (lua_gc(m_LuaState, LUA_GCCOUNTB, 0) << 0);
}


void NLuaMonsterAIMgr::InsertMSG_DEAD(const int in_SvrScriptAppID, const unsigned long in_AID)
{
	APP_CONTAINER_ITER iter = m_AppContainer.find(in_SvrScriptAppID);
	if( iter == m_AppContainer.end() )
		return;

	iter->second->NLuaMonsterAI::InsertMSG_DEAD(in_AID);
}


void NLuaMonsterAIMgr::InsertMSG_ATTACKED(const int in_SvrScriptAppID, const unsigned long in_AID, const int in_Damage)
{
	APP_CONTAINER_ITER iter = m_AppContainer.find(in_SvrScriptAppID);
	if( iter == m_AppContainer.end() )
		return;

	iter->second->NLuaMonsterAI::InsertMSG_ATTACKED(in_AID, in_Damage);
}


void NLuaMonsterAIMgr::InsertMSG_LOG(const int in_SvrScriptAppID)
{
	APP_CONTAINER_ITER iter = m_AppContainer.find(in_SvrScriptAppID);
	if( iter == m_AppContainer.end() )
		return;

	iter->second->NLuaMonsterAI::InsertMSG_LOG();
}


void NLuaMonsterAIMgr::InsertMSG_TELEPORT(const int in_SvrScriptAppID, const int in_xPos, const int in_yPos, const char* in_MapName)
{
	APP_CONTAINER_ITER iter = m_AppContainer.find(in_SvrScriptAppID);
	if( iter == m_AppContainer.end() )
		return;

	iter->second->NLuaMonsterAI::InsertMSG_TELEPORT(in_xPos, in_yPos, in_MapName);
}
