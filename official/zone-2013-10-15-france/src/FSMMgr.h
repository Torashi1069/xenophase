#pragma once
#include "FSM.h"


struct SCRIPT_INPUT
{
	/* this+ 0 */ unsigned long npcTypeID;
	/* this+ 4 */ unsigned long fsmStateID;
	/* this+ 8 */ unsigned long inputType;
	/* this+12 */ unsigned long outputType;
	/* this+16 */ unsigned long outputState;
};


class CFSMMgr
{
public:
	CFSMMgr();
	virtual ~CFSMMgr();

public:
	void Init();
	void Load(); // not implemented
	void LoadScript(const char* filename, int verDate);
	void Insert(char* , char* , char* , char* , char* ); // not implemented
	CFSM* GetFSM(unsigned long fsmID);
	void Destroy();
	unsigned long GetKeyWord(const char* strKeyWord);
	int Load_FSM_NpcScript();
	bool SetDefined(const char* npcTypeID, const char* fsmStateID, const char* inputType, const char* outputType, const char* outputState);

private:
	void AddFSM(SCRIPT_INPUT* inputData);
	void DeleteFSM(unsigned long npcTypeID);

private:
	/* this+ 0 */ //const CFSMMgr::`vftable';
	/* this+ 4 */ std::map<std::string,unsigned long> m_scriptKeyword;
	/* this+20 */ std::map<unsigned long,CFSM*> m_fsm;
};
