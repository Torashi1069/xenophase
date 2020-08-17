// e:\해외빌드\2009-09-21\ragnarokserver\zoneprocess\pc.cpp
#include "globals.hpp"
#include "CCharInfoDB.hpp"
#include "PC.h"
#include "MannerPointInfo.hpp"
#include "shared.h" // Trace


void MannerPointInfo::Init(CPC* pc)
{
	this->m_owner = pc;
	this->MannerPointInfo::Reset();
}


void MannerPointInfo::Reset(void)
{
	this->m_info.clear();
}


unsigned long MannerPointInfo::IsGivableMP(unsigned long otherGID)
{
	_SYSTEMTIME st;
	GetLocalTime(&st);

	if( this->MannerPointInfo::SearchOtherCharacter(otherGID) )
		return 2;

	if( m_lastTimeGivingMP == st.wDay )
		return 1;

	if( this->MannerPointInfo::GetSize() >= 30 )
		this->MannerPointInfo::DeleteFirstRecord();

	m_lastTimeGivingMP = st.wDay;
	return 0;
}


int MannerPointInfo::LoadMPInfo(void)
{
	return g_charInfoDB->CCharInfoDB::LoadMPInfo(m_owner->GetAccountID(), &m_info, m_lastTimeGivingMP);
}


void MannerPointInfo::InsertNewMP(unsigned long otherGID, int type)
{
	Trace("InsertNewMP gid:%d, type:%d\n", otherGID, type);
	g_charInfoDB->CCharInfoDB::InsertNewMP(m_owner->GetAccountID(), otherGID, type);
}


int MannerPointInfo::SearchOtherCharacter(unsigned long otherGID)
{
	for( mystd::list<MannerPointData>::iterator it = m_info.begin(); it != m_info.end(); ++it )
		if( it->otherGID == otherGID )
			return 1;
	return 0;
}


int MannerPointInfo::GetSize(void)
{
	return m_info.size();
}


int MannerPointInfo::DeleteFirstRecord(void)
{
	unsigned long otherGID = m_info.begin()->otherGID;
	m_info.pop_front();
	g_charInfoDB->CCharInfoDB::DeleteMP(m_owner->GetAccountID(), otherGID);
	return -1;
}
