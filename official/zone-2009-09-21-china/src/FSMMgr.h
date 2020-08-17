#pragma once
#include "FSM.h"
#include "std/map"
#include "std/string"


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
	/* this+ 0 */ public: //const CFSMMgr::`vftable';
	/* this+ 4 */ private: mystd::map<mystd::string,unsigned long> m_scriptKeyword;
	/* this+10 */ private: mystd::map<unsigned long,CFSM*> m_fsm;

	public: CFSMMgr::CFSMMgr(void);
	public: virtual CFSMMgr::~CFSMMgr(void);
	public: void CFSMMgr::Init(void);
	//public: void CFSMMgr::Load(void);
	public: void CFSMMgr::LoadScript(const char* filename, int verDate);
	//public: void CFSMMgr::Insert(char*, char*, char*, char*, char*);
	public: CFSM* CFSMMgr::GetFSM(unsigned long fsmID);
	public: void CFSMMgr::Destroy(void);
	public: unsigned long CFSMMgr::GetKeyWord(const char* strKeyWord);
	public: int CFSMMgr::Load_FSM_NpcScript(void);
	public: bool CFSMMgr::SetDefined(const char* npcTypeID, const char* fsmStateID, const char* inputType, const char* outputType, const char* outputState);
	private: void CFSMMgr::AddFSM(SCRIPT_INPUT* inputData);
	private: void CFSMMgr::DeleteFSM(unsigned long npcTypeID);

private:
	static hook_method<void (CFSMMgr::*)(void)> CFSMMgr::_Init;
	static hook_method<void (CFSMMgr::*)(const char* filename, int verDate)> CFSMMgr::_LoadScript;
	static hook_method<CFSM* (CFSMMgr::*)(unsigned long fsmID)> CFSMMgr::_GetFSM;
	static hook_method<void (CFSMMgr::*)(void)> CFSMMgr::_Destroy;
	static hook_method<unsigned long (CFSMMgr::*)(const char* strKeyWord)> CFSMMgr::_GetKeyWord;
	static hook_method<int (CFSMMgr::*)(void)> CFSMMgr::_Load_FSM_NpcScript;
	static hook_method<bool (CFSMMgr::*)(const char* npcTypeID, const char* fsmStateID, const char* inputType, const char* outputType, const char* outputState)> CFSMMgr::_SetDefined;
	static hook_method<void (CFSMMgr::*)(SCRIPT_INPUT* inputData)> CFSMMgr::_AddFSM;
	static hook_method<void (CFSMMgr::*)(unsigned long npcTypeID)> CFSMMgr::_DeleteFSM;
};
