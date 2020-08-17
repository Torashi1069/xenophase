#include "FSMState.h"


CFSMState::CFSMState(void) // line 7
{
	memset(m_table, 0, sizeof(m_table));
}


CFSMState::~CFSMState(void) // line 12
{
	this->CFSMState::Destroy();
}


hook_method<void (CFSMState::*)(unsigned long stateID)> CFSMState::_Init(SERVER, "CFSMState::Init");
void CFSMState::Init(unsigned long stateID) // line 17
{
	return (this->*_Init)(stateID);

	this->CFSMState::Destroy();
	m_count = 0;
	memset(m_table, 0, sizeof(m_table));
}


hook_method<void (CFSMState::*)(void)> CFSMState::_Destroy(SERVER, "CFSMState::Destroy");
void CFSMState::Destroy(void) // line 26
{
	return (this->*_Destroy)();

	for( int i = 0; i < countof(m_table); ++i )
		delete m_table[i];
}


hook_method<int (CFSMState::*)(unsigned long inputType, unsigned long& outputType, unsigned long& outputState)> CFSMState::_GetOutput(SERVER, "CFSMState::GetOutput");
int CFSMState::GetOutput(unsigned long inputType, unsigned long& outputType, unsigned long& outputState) // line 35
{
	return (this->*_GetOutput)(inputType, outputType, outputState);

	if( inputType >= countof(m_table) )
		return 0;
	
	if( m_table[inputType] == NULL )
		return 0;

	outputType = m_table[inputType]->outputType;
	outputState = m_table[inputType]->outputState;
	return 1;
}


hook_method<void (CFSMState::*)(unsigned long inputType, unsigned long outputType, unsigned long outputState)> CFSMState::_AddTransition(SERVER, "CFSMState::AddTransition");
void CFSMState::AddTransition(unsigned long inputType, unsigned long outputType, unsigned long outputState) // line 48
{
	return (this->*_AddTransition)(inputType, outputType, outputState);

	OUTPUT_DATA* out = new OUTPUT_DATA;
	out->outputState = outputState;
	out->outputType = outputType;

	m_table[inputType] = out;
	m_transition[m_count++] = inputType;
}
