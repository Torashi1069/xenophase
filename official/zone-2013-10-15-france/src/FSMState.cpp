#include "FSMState.h"


CFSMState::CFSMState()
{
//	m_count = 0;
//	memset(m_transition, 0, sizeof(m_transition));
	memset(m_table, (int)NULL, sizeof(m_table));
}


CFSMState::~CFSMState()
{
	this->CFSMState::Destroy();
}


void CFSMState::Init(unsigned long stateID)
{
	this->CFSMState::Destroy();
	m_count = 0;
	memset(m_table, (int)NULL, sizeof(m_table));
}


void CFSMState::Destroy()
{
	for( size_t i = 0; i < countof(m_table); ++i )
		delete m_table[i];
}


BOOL CFSMState::GetOutput(unsigned long inputType, unsigned long& outputType, unsigned long& outputState)
{
	if( inputType >= countof(m_table) )
		return FALSE;

	OUTPUT_DATA* outputData = m_table[inputType];
	if( outputData == NULL )
		return FALSE;

	outputType = outputData->outputType;
	outputState = outputData->outputState;
	return TRUE;
}


void CFSMState::AddTransition(unsigned long inputType, unsigned long outputType, unsigned long outputState)
{
	OUTPUT_DATA* outputData = new OUTPUT_DATA;
	outputData->outputState = outputState;
	outputData->outputType = outputType;

	m_table[inputType] = outputData;
	m_transition[m_count] = inputType;
	++m_count;
}
