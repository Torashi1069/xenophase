#pragma once


struct OUTPUT_DATA
{
	/* this+0 */ unsigned long outputType;
	/* this+4 */ unsigned long outputState;
};


class CFSMState
{
	/* this+ 0 */ public: //const CFSMState::`vftable';
	/* this+ 4 */ private: int m_count; // nTransitions
	/* this+ 8 */ private: unsigned long m_transition[10];
	/* this+48 */ private: OUTPUT_DATA* m_table[64];

	public: CFSMState::CFSMState(void);
	public: virtual CFSMState::~CFSMState(void);
	public: void CFSMState::AddTransition(unsigned long inputType, unsigned long outputType, unsigned long outputState);
	public: int CFSMState::GetOutput(unsigned long inputType, unsigned long& outputType, unsigned long& outputState);
	public: void CFSMState::Init(unsigned long stateID);
	private: void CFSMState::Destroy(void);

private:
	static hook_method<void (CFSMState::*)(unsigned long inputType, unsigned long outputType, unsigned long outputState)> CFSMState::_AddTransition;
	static hook_method<int (CFSMState::*)(unsigned long inputType, unsigned long& outputType, unsigned long& outputState)> CFSMState::_GetOutput;
	static hook_method<void (CFSMState::*)(unsigned long stateID)> CFSMState::_Init;
	static hook_method<void (CFSMState::*)(void)> CFSMState::_Destroy;

	friend class CNPCStateUpdater;
};
