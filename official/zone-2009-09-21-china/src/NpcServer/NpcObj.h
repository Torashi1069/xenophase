#pragma once
#include "ScriptLib/TokenData.h"
#include "struct.hpp"


class CNpc
{
public:
	CNpc();
	~CNpc();

public:
	void Clear();
	int GetId();
	int GetType();
	char* GetName();
	void SetInfo(int id, const NpcSvrNpcInfo* npcInfo);
	//int GetLocalVarIdx(char*);
	//bool SetLocalVarName(int, const char*);
	//int GetLocalVar(int);
	//char* GetLocalVarName(int);
	//void IncLocalVar(int, int);
	//void DecLocalVar(int, int);
	//void SetLocalVar(int, int);
	//void InitTimer();
	void OnTimer();
	void PauseTimer();
	//void AddTimer(unsigned long);
	//void SubTimer(unsigned long);
	//int SetActionScript(int, int, mystd::deque<TokenData>&);
	//int GetActionScriptIdx(int, int, char*);
	//int GetActionScriptPos(int);
	//bool GetOnInit();
	void SetOnInit(bool b);
	//int IsNpcType();
	char* GetMapName();

private:
	/* this+   0 */ int m_id;
	/* this+   4 */ int m_type;
	/* this+   8 */ mystd::string m_name;
	/* this+  36 */ int m_npcType;
	/* this+  40 */ char m_mapName[16];
	/* this+  56 */ int m_param[16];
	/* this+ 120 */ char m_ParamName[16][100];
	/* this+1720 */ int m_actionScriptPos[50];
	/* this+1920 */ TokenData m_actionScriptParam[50];
	/* this+3720 */ int m_actionScriptAction[50];
	/* this+3920 */ int m_actionScriptOnTimerActIdx[50];
	/* this+4120 */ int m_timerEventNo;
	/* this+4124 */ unsigned long m_baseTime;
	/* this+4128 */ int m_onTimerActIdx;
	/* this+4132 */ int m_onTimerActNo;
	/* this+4136 */ int m_actCount;
	/* this+4140 */ bool m_OnInit;
};
