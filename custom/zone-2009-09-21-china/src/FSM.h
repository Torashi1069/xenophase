#pragma once
#include "FSMState.h"
#include "std/map"


class CFSM
{
	/* this+0 */ public: //const CFSM::`vftable';
	/* this+4 */ private: unsigned long m_fsmID;
	/* this+8 */ private: mystd::map<unsigned long,CFSMState*> m_fsmState;

	public: CFSM::CFSM(void);
	public: virtual CFSM::~CFSM(void);
	public: void CFSM::Init(unsigned long fsmID);
	public: CFSMState* CFSM::GetFSMState(unsigned long stateID);
	public: void CFSM::DeleteState(unsigned long stateID);
	public: void CFSM::AddFSMState(unsigned long stateID, unsigned long inputType, unsigned long outputType, unsigned long outputState);
	public: void CFSM::Destroy(void);

private:
	static hook_method<void (CFSM::*)(unsigned long fsmID)> CFSM::_Init;
	static hook_method<CFSMState* (CFSM::*)(unsigned long stateID)> CFSM::_GetFSMState;
	static hook_method<void (CFSM::*)(unsigned long stateID)> CFSM::_DeleteState;
	static hook_method<void (CFSM::*)(unsigned long stateID, unsigned long inputType, unsigned long outputType, unsigned long outputState)> CFSM::_AddFSMState;
	static hook_method<void (CFSM::*)(void)> CFSM::_Destroy;
};
