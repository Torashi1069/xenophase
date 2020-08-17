#include "Item.h"
#include "Common/Packet.h"


const char* CItem::GetName() // ???
{
	return m_itemInfo.name;
}


void CItem::CheckStateChange() // 112-116
{
	if( m_pickableType == PICKABLETYPE_PARTYUSER )
	{
		if( timeGetTime() > m_itemInfo.MoveReqLastTime + m_pickableTime )
			m_pickableType = PICKABLETYPE_KILLUSER;
	}
}


int CItem::OnProcess() // 119-128
{
	this->CItem::CheckStateChange();

	if( timeGetTime() > m_itemInfo.MoveReqLastTime + 60000 )
		return 0; // item expired.

	return -1;
}


void CItem::OnDisappear() // 287-298
{
	PACKET_ZC_ITEM_DISAPPEAR outpacket;
	outpacket.PacketType = HEADER_ZC_ITEM_DISAPPEAR;
	outpacket.ITAID = this->m_ITAID;
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CItem::SetPickableTime(unsigned long time) // ??? (105.h)
{
	m_pickableTime = time;
}
