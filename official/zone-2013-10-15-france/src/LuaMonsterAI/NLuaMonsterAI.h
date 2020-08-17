#pragma once
#include "LuaMonsterAI/NLuaMonsterAIMsg.h"
#include "shared/NLuaThread.h"


class NLuaMonsterAI
{
private:
	enum enumProcessFuncStep
	{
		PROCESSFUNC_STEP_NONE  = 0,
		PROCESSFUNC_STEP_EXEC  = 1,
		PROCESSFUNC_STEP_EXIT  = 2,
		PROCESSFUNC_STEP_ERROR = 3,
	};

public:
	typedef std::tr1::shared_ptr<LuaMonsterAIStuff::NMSG> MSG_SHARDPTR;

public:
	void InsertMSG_ATTACKED(const unsigned long in_AID, const int in_Damage);
	void InsertMSG_DEAD(const unsigned long in_AID);
	void InsertMSG_LOG();
	void InsertMSG_TELEPORT(const int in_xPos, const int in_yPos, const char* in_MapName);
	void SetProcessFuncStep(const enumProcessFuncStep in_Step);
	enumProcessFuncStep GetProcessFuncStep();
	unsigned long GetProcessFuncStepTime();
	lua_State* GetStatePtr();
	bool IsForceProcessing();
	const int GetID();
	const char* GetNamePtr();
	const int GetRef();
	unsigned long GetAID();
	std::pair<bool,MSG_SHARDPTR> GetAsyncMsg();
	void Init(const std::string in_Name, NLuaThread* in_pThread, const int in_Ref);

private:
	NLuaMonsterAI(const int in_ID, const unsigned long in_AID, const bool in_bForceProcessing);
	virtual ~NLuaMonsterAI();

private:
	/* this+0 */ //const NLuaMonsterAI::`vftable';
	typedef std::list<MSG_SHARDPTR> MESSAGEQUEUE;
	typedef std::list<MSG_SHARDPTR>::iterator MESSAGEQUEUE_ITER;
	/* this+4 */ MESSAGEQUEUE m_MessageQueue;

private:
	class NStep
	{
	public:
		enumProcessFuncStep Get() { return m_Step; }
		void Set(enumProcessFuncStep in_Step) { m_Step = in_Step; m_Time = timeGetTime(); }
		unsigned long GetTime() { return m_Time; }

	private:
		/* this+0 */ enumProcessFuncStep m_Step;
		/* this+4 */ unsigned long m_Time;

	public:
		NStep() : m_Step(PROCESSFUNC_STEP_NONE), m_Time(timeGetTime()) { }
		~NStep() { }
	};

private:
	/* this+16 */ NLuaThread* m_pThread;
	/* this+20 */ int m_Ref;
	/* this+24 */ std::string m_Name;
	/* this+52 */ const int m_ID;
	/* this+56 */ NStep m_ProcFuncStep;
	/* this+64 */ const unsigned long m_AID;
	/* this+68 */ const bool m_bForceProcessing;

private:
	friend class NLuaMonsterAIMgr;
};
