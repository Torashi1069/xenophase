#pragma once
#include "ScriptLib/TokenData.h"


enum enumNPCEVENT
{
	NPCEVENT_ONINIT          = 1,
	NPCEVENT_ONCLICK         = 2,
	NPCEVENT_ONTOUCH         = 3,
	NPCEVENT_ONMYMOBDEAD     = 4,
	NPCEVENT_ONTIMER         = 5,
	NPCEVENT_ONCOMMAND       = 6,
	NPCEVENT_ONSTARTARENA    = 7,
	NPCEVENT_ONTOUCHNPC      = 8,
	NPCEVENT_ONTOUCH2        = 9,
	NPCEVENT_ONMOVENPCCMD   = 10,
	NPCEVENT_ONCAMPCOMMAND  = 11,
	NPCEVENT_ONCAMPCOMMAND2 = 12,
	NPCEVENT_ONAGITINVEST   = 13,
};


struct NpcSvrNpcInfo
{
	/* this+ 0 */ const char* zone;
	/* this+ 4 */ const char* name;
	/* this+ 8 */ int type;
	/* this+12 */ int x;
	/* this+16 */ int y;
	/* this+20 */ int dx;
	/* this+24 */ int dy;
	/* this+28 */ int w;
	/* this+32 */ int h;
	/* this+36 */ int sprite;
	/* this+40 */ int direction;
	/* this+44 */ int regenMin;
	/* this+48 */ int regenMax;
	/* this+52 */ int regenType;
	/* this+56 */ int npcType;

	void SetDefault()
	{
		this->zone = 0;
		this->name = 0;
		this->type = 0;
		this->x = 0;
		this->y = 0;
		this->dx = 0;
		this->dy = 0;
		this->w = 0;
		this->h = 0;
		this->sprite = 32;
		this->direction = 0;
		this->regenMin = 1000;
		this->regenMax = 4000;
		this->regenType = 0;
		this->npcType = 0;
	}
};


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
	int GetLocalVarIdx(char* varName);
	bool SetLocalVarName(int slot, const char* name);
	int GetLocalVar(int idx);
	char* GetLocalVarName(int idx);
	void IncLocalVar(int idx, int val);
	void DecLocalVar(int idx, int val);
	void SetLocalVar(int idx, int val);
	void InitTimer();
	void OnTimer();
	void PauseTimer();
	void AddTimer(unsigned long num);
	void SubTimer(unsigned long num);
	int SetActionScript(int action, int pos, std::deque<TokenData>& parm);
	int GetActionScriptIdx(int act, int nParam, char* strParam);
	int GetActionScriptPos(int index);
	bool GetOnInit() const;
	void SetOnInit(bool b);
	int IsNpcType();
	char* GetMapName();

private:
	/* this+   0 */ int m_id;
	/* this+   4 */ int m_type;
	/* this+   8 */ std::string m_name;
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
