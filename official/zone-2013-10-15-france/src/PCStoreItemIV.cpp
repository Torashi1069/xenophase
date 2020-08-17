#include "PCItemInventoryMgr.h"
#include "PCStoreItemIV.h"
#include "Request.h"
#include "Common/Packet.h"


CPCStoreItemIV::CPCStoreItemIV()
{
}


CPCStoreItemIV::~CPCStoreItemIV()
{
}


void CPCStoreItemIV::Init()
{
	m_isStoreOpen = FALSE;
	this->CPCItemInventory::Init();
}


BOOL CPCStoreItemIV::Delete(short index, short count)
{
	if( !this->CPCItemInventory::Delete(index, count) )
		return FALSE;

	PACKET_ZC_DELETE_ITEM_FROM_STORE outpacket;
	outpacket.PacketType = HEADER_ZC_DELETE_ITEM_FROM_STORE;
	outpacket.index = index;
	outpacket.count = count;

	Request request;
	request.Request::SetID(RT_SEND_PACKET);
	request.par1 = sizeof(outpacket);
	request.par2 = (int)&outpacket;
	m_owner->CPCItemInventoryMgr::OnMediatorRequest(&request);

	return TRUE;
}


IVItItem* CPCStoreItemIV::Remove(short index, short count)
{
	IVItItem* item = this->CPCItemInventory::Remove(index, count);
	if( item == NULL )
		return NULL;

	PACKET_ZC_DELETE_ITEM_FROM_STORE outpacket;
	outpacket.PacketType = HEADER_ZC_DELETE_ITEM_FROM_STORE;
	outpacket.count = count;
	outpacket.index = index;

	Request request;
	request.Request::SetID(RT_SEND_PACKET);
	request.par1 = sizeof(outpacket);
	request.par2 = (int)&outpacket;
	m_owner->CPCItemInventoryMgr::OnMediatorRequest(&request);

	return item;
}


void CPCStoreItemIV::Reset()
{
	m_isStoreOpen = FALSE;
	this->CPCItemInventory::Reset();
}


BOOL CPCStoreItemIV::IsOpen()
{
	return m_isStoreOpen;
}


void CPCStoreItemIV::SetStoreOpenFlag(BOOL flag)
{
	m_isStoreOpen = flag;
}
