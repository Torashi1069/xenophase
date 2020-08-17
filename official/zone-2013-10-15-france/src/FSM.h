#pragma once
#include "FSMState.h"


class CFSM
{
public:
	CFSM();
	virtual ~CFSM();

public:
	void Init(unsigned long fsmID);
	CFSMState* GetFSMState(unsigned long stateID);
	void DeleteState(unsigned long stateID);
	void AddFSMState(unsigned long stateID, unsigned long inputType, unsigned long outputType, unsigned long outputState);
	void Destroy();

private:
	/* this+0 */ //const CFSM::`vftable';
	/* this+4 */ unsigned long m_fsmID;
	/* this+8 */ std::map<unsigned long,CFSMState*> m_fsmState;
};
