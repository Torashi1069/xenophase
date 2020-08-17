#include "FSM.h"


CFSM::CFSM()
{
}


CFSM::~CFSM()
{
	this->CFSM::Destroy();
}


void CFSM::Init(unsigned long fsmID)
{
	this->CFSM::Destroy();
	m_fsmID = fsmID;
}


CFSMState* CFSM::GetFSMState(unsigned long stateID)
{
	std::map<unsigned long,CFSMState*>::iterator iter = m_fsmState.find(stateID);
	if( iter == m_fsmState.end() )
		return NULL;

	return iter->second;
}


void CFSM::DeleteState(unsigned long stateID)
{
	std::map<unsigned long,CFSMState*>::iterator iter = m_fsmState.find(stateID);
	if( iter == m_fsmState.end() )
		return;

	delete iter->second;
	m_fsmState.erase(iter);
}


void CFSM::AddFSMState(unsigned long stateID, unsigned long inputType, unsigned long outputType, unsigned long outputState)
{
	std::map<unsigned long,CFSMState*>::iterator iter = m_fsmState.find(stateID);
	if( iter == m_fsmState.end() )
	{
		CFSMState* state = new CFSMState();
		state->CFSMState::Init(stateID);
		state->CFSMState::AddTransition(inputType, outputType, outputState);
		m_fsmState[stateID] = state;
	}
	else
	{
		CFSMState* state = iter->second;
		state->CFSMState::AddTransition(inputType, outputType, outputState);
	}
}


void CFSM::Destroy()
{
	for( std::map<unsigned long,CFSMState*>::iterator iter = m_fsmState.begin(); iter != m_fsmState.end(); iter = m_fsmState.erase(iter) )
		delete iter->second;
}
