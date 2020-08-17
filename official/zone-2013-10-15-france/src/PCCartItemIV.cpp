#include "PCItemInventoryMgr.h"
#include "PCCartItemIV.h"
#include "Request.h"
#include "Common/Packet.h"


CPCCartItemIV::CPCCartItemIV()
{
}


CPCCartItemIV::~CPCCartItemIV()
{
}


void CPCCartItemIV::Init()
{
	m_isFirstCartOn = FALSE;
	this->CPCItemInventory::Init();
}


IVItItem* CPCCartItemIV::Add(IVItItem* item, int par1, BOOL isIndexChangable)
{
	return this->CPCItemInventory::Add(item, 0, TRUE);
}


BOOL CPCCartItemIV::Delete(short index)
{
	return this->CPCItemInventory::Delete(index);
}


BOOL CPCCartItemIV::Delete(short index, short count)
{
	if( !this->CPCItemInventory::Delete(index, count) )
		return FALSE;

	PACKET_ZC_DELETE_ITEM_FROM_CART outpacket;
	outpacket.PacketType = HEADER_ZC_DELETE_ITEM_FROM_CART;
	outpacket.index = index;
	outpacket.count = count;

	Request request;
	request.Request::SetID(RT_SEND_PACKET);
	request.par1 = sizeof(outpacket);
	request.par2 = (int)&outpacket;
	m_owner->CPCItemInventoryMgr::OnMediatorRequest(&request);

	return TRUE;
}


IVItItem* CPCCartItemIV::Remove(short index, short count)
{
	IVItItem* item = this->CPCItemInventory::Remove(index, count);
	if( item == NULL )
		return NULL;

	PACKET_ZC_DELETE_ITEM_FROM_CART outpacket;
	outpacket.PacketType = HEADER_ZC_DELETE_ITEM_FROM_CART;
	outpacket.count = count;
	outpacket.index = index;

	Request request;
	request.Request::SetID(RT_SEND_PACKET);
	request.par1 = sizeof(outpacket);
	request.par2 = (int)&outpacket;
	m_owner->CPCItemInventoryMgr::OnMediatorRequest(&request);

	return item;
}


void CPCCartItemIV::SetCartOnFlag(int flag)
{
	m_isFirstCartOn = flag;
}


BOOL CPCCartItemIV::IsCartOn()
{
	return m_isFirstCartOn;
}


void CPCCartItemIV::Reset()
{
	m_isFirstCartOn = FALSE;
	this->CPCItemInventory::Reset();
}
