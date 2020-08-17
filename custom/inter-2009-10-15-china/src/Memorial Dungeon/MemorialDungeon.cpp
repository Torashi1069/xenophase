#include "MemorialDungeon.h"


hook_method<unsigned long (CMemorialDungeon::*)(const enum CMemorialDungeon::enumSCHEDULE in_Job)> CMemorialDungeon::_Schedule_GetDate(SERVER, "CMemorialDungeon::Schedule_GetDate");
unsigned long CMemorialDungeon::Schedule_GetDate(const enum CMemorialDungeon::enumSCHEDULE in_Job) // line 308-313
{
	return (this->*_Schedule_GetDate)(in_Job);

	// TODO
}


hook_method<const mystd::string (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetName(SERVER, "CMemorialDungeon::GetName");
const mystd::string CMemorialDungeon::GetName(void) // line 108 (MemorialDungeon.h)
{
	return (this->*_GetName)();

	return m_Name;
}


hook_method<const unsigned long (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetPartyID(SERVER, "CMemorialDungeon::GetPartyID");
const unsigned long CMemorialDungeon::GetPartyID(void) // line 109 (MemorialDungeon.h)
{
	return (this->*_GetPartyID)();

	return m_hParty;
}


hook_method<const unsigned long (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetLiveDate(SERVER, "CMemorialDungeon::GetLiveDate");
const unsigned long CMemorialDungeon::GetLiveDate(void) // line 111 (MemorialDungeon.h)
{
	return (this->*_GetLiveDate)();

	return this->CMemorialDungeon::Schedule_GetDate(CMemorialDungeon::SCHEDULE_DESTORY_LIVE_TIMEOUT);
}


hook_method<const unsigned long (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetEnterLimitDate(SERVER, "CMemorialDungeon::GetLiveDate");
const unsigned long CMemorialDungeon::GetEnterLimitDate(void) // line 112 (MemorialDungeon.h)
{
	return (this->*_GetEnterLimitDate)();

	return this->CMemorialDungeon::Schedule_GetDate(CMemorialDungeon::SCHEDULE_DESTORY_ENTER_TIMEOUT);
}


hook_method<void (CMemorialDungeon::*)(const unsigned long in_AID, const unsigned long in_GID)> CMemorialDungeon::_PartyLeave(SERVER, "CMemorialDungeon::PartyLeave");
void CMemorialDungeon::PartyLeave(const unsigned long in_AID, const unsigned long in_GID) // line 346
{
	return (this->*_PartyLeave)(in_AID,in_GID);

	// TODO
}


hook_method<const enum CMemorialDungeon::enumSTATE (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetState(SERVER, "CMemorialDungeon::GetState");
const enum CMemorialDungeon::enumSTATE CMemorialDungeon::GetState(void) // line 121
{
	return (this->*_GetState)();

	return m_State;
}
