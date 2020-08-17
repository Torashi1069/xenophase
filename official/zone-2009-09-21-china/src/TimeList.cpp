#include "TimeList.h"


CTimeList::CTimeList(void) // line 13
{
}


CTimeList::~CTimeList(void) // line 18
{
}


hook_method<bool (CTimeList::*)(void)> CTimeList::_IsTimeListFull(SERVER, "CTimeList::IsTimeListFull");
bool CTimeList::IsTimeListFull(void) // line 28
{
	return (this->*_IsTimeListFull)();

	return ( m_index2Time.size() >= MAX_TIMELIST_SIZE );
}


hook_method<time_t (CTimeList::*)(int ti)> CTimeList::_FindTimeList(SERVER, "CTimeList::FindTimeList");
time_t CTimeList::FindTimeList(int ti) // line 39
{
	return (this->*_FindTimeList)(ti);

	if( m_index2Time.find(ti) == m_index2Time.end() )
		return -1;

	return max(0, time(NULL) - m_index2Time[ti]);
}


hook_method<int (CTimeList::*)(int ti)> CTimeList::_AddTimeList(SERVER, "CTimeList::AddTimeList");
int CTimeList::AddTimeList(int ti) // line 55
{
	return (this->*_AddTimeList)(ti);

	if( m_index2Time.size() >= MAX_TIMELIST_SIZE )
		return 1;

	if( m_index2Time.find(ti) != m_index2Time.end() )
		return 2;

	m_index2Time[ti] = time(NULL);
	return 0;
}


hook_method<bool (CTimeList::*)(int ti, int delta)> CTimeList::_SetTimeList(SERVER, "CTimeList::SetTimeList");
bool CTimeList::SetTimeList(int ti, int delta) // line 83
{
	return (this->*_SetTimeList)(ti, delta);

	if( m_index2Time.find(ti) == m_index2Time.end() )
		return false;

	m_index2Time[ti] += delta;
	return true;
}


hook_method<int (CTimeList::*)(unsigned char* buf, int& len)> CTimeList::_WriteBinary(SERVER, "CTimeList::WriteBinary");
int CTimeList::WriteBinary(unsigned char* buf, int& len) // line ???
{
	return (this->*_WriteBinary)(buf, len);

	//TODO
}


hook_method<void (CTimeList::*)(mystd::string& str)> CTimeList::_DisplayTimeList(SERVER, "CTimeList::DisplayTimeList");
void CTimeList::DisplayTimeList(mystd::string& str) // line 157
{
	return (this->*_DisplayTimeList)(str);

	//TODO
}
