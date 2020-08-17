#pragma once
#include "LuaMonsterAI/NLuaMonsterAI.h"
#include "shared/NLuaState.h"


class NLuaMonsterAIMgr
{
public:
	NLuaState& GetLuaState();

private:
	/* static  */ static NLuaMonsterAIMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const NLuaMonsterAIMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ NLuaState m_LuaState;

private:
	struct tagLuaGlueFunc
	{
		/* this+0 */ int (*func)(lua_State* L);
		/* this+4 */ const char* name;
	};

	/* static  */ static const tagLuaGlueFunc m_LuaGlueFuncTable[];

private:
	typedef std::map<int,NLuaMonsterAI*> APP_CONTAINER;
	typedef std::map<int,NLuaMonsterAI*>::iterator APP_CONTAINER_ITER;
	/* this+20 */ APP_CONTAINER m_AppContainer;

private:
	bool Create();
	void Destroy();
	int GetNewAppID();
	void AppResume(NLuaMonsterAI* in_cpApp, const int in_NArg);

public:
	int CreateApp(unsigned long in_AID, const std::string in_Name, const bool in_bForceProcessing);
	void DestroyApp(const int in_AppID);
	bool isOK() const;
	std::pair<bool,std::string> Init();
	void Process();
	int GetUsedMemoryBytes();
	NLuaMonsterAI* GetAppPtr(const int in_SvrScriptAppID) const;
	void InsertMSG_ATTACKED(const int in_SvrScriptAppID, const unsigned long in_AID, const int in_Damage);
	void InsertMSG_DEAD(const int in_SvrScriptAppID, const unsigned long in_AID);
	void InsertMSG_LOG(const int in_SvrScriptAppID);
	void InsertMSG_TELEPORT(const int in_SvrScriptAppID, const int in_xPos, const int in_yPos, const char* in_MapName);
	void WriteLog(); //TODO

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static NLuaMonsterAIMgr* GetObj(); /// @custom

private:
	NLuaMonsterAIMgr();
	virtual ~NLuaMonsterAIMgr();
};
