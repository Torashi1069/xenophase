#include "PCBattleMercenary.h"


CPCBattleMercenary::CPCBattleMercenary() // 11-13
{
	this->CPCBattleMercenary::Clear();
}


CPCBattleMercenary::~CPCBattleMercenary() // 16-18
{
}


void CPCBattleMercenary::Clear() // 23-30
{
	m_bCall = false;
	m_bModify = false;
	m_TypicalJobInfoContainer.clear();
	m_WorkStep = WORKSTEP_NONE;
	m_ProxyDB.m_bLoad = false;
}
