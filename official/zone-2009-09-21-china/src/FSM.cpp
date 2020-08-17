#include "FSM.h"


CFSM::CFSM(void) // line 6
{
}


CFSM::~CFSM(void) // line 10
{
	this->CFSM::Destroy();
}


hook_method<void (CFSM::*)(unsigned long fsmID)> CFSM::_Init(SERVER, "CFSM::Init");
void CFSM::Init(unsigned long fsmID) // line 15
{
	return (this->*_Init)(fsmID);

	this->CFSM::Destroy();
	m_fsmID = fsmID;
}


hook_method<CFSMState* (CFSM::*)(unsigned long stateID)> CFSM::_GetFSMState(SERVER, "CFSM::GetFSMState");
CFSMState* CFSM::GetFSMState(unsigned long stateID) // line 21
{
	return (this->*_GetFSMState)(stateID);

	mystd::map<unsigned long,CFSMState*>::iterator it = m_fsmState.find(stateID);
	return ( it != m_fsmState.end() ) ? it->second : NULL;
}


//hook_method<void (CFSM::*)(unsigned long stateID)> CFSM::_DeleteState(SERVER, "CFSM::DeleteState");
void CFSM::DeleteState(unsigned long stateID) // line ??
{
//	return (this->*_DeleteState)(stateID);

	mystd::map<unsigned long,CFSMState*>::iterator it = m_fsmState.find(stateID);
	if( it != m_fsmState.end() )
	{
		delete it->second;
		m_fsmState.erase(it);
	}
}


hook_method<void (CFSM::*)(unsigned long stateID, unsigned long inputType, unsigned long outputType, unsigned long outputState)> CFSM::_AddFSMState(SERVER, "CFSM::AddFSMState");
void CFSM::AddFSMState(unsigned long stateID, unsigned long inputType, unsigned long outputType, unsigned long outputState) // line 42
{
	return (this->*_AddFSMState)(stateID, inputType, outputType, outputState);

	mystd::map<unsigned long,CFSMState*>::iterator it = m_fsmState.find(stateID);
	if( it == m_fsmState.end() )
	{
		CFSMState* state = new CFSMState();
		state->CFSMState::Init(stateID);
		state->CFSMState::AddTransition(inputType, outputType, outputState);
		m_fsmState[stateID] = state;
	}
	else
	{
		CFSMState* state = it->second;
		state->CFSMState::AddTransition(inputType, outputType, outputState);
	}
}


hook_method<void (CFSM::*)(void)> CFSM::_Destroy(SERVER, "CFSM::Destroy");
void CFSM::Destroy(void) // line 56
{
	return (this->*_Destroy)();

	mystd::map<unsigned long,CFSMState*>::iterator it = m_fsmState.begin();
	while( it != m_fsmState.end() )
	{
		delete it->second;
		it = m_fsmState.erase(it);
	}
}
