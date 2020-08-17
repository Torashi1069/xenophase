#include "ITPMgr.h"
#include "PC.h"
#include "PCHireItemCtrl.h"
#include "Common/Packet.h"
#include "Player/Inventory/CIVItItem.h"
#include "shared/NCriticalErrorLog.h"


CPCHireItemCtrl::CPCHireItemCtrl()
: m_ReqContainer(), m_cpMyOwnerPC(NULL)
{
}


CPCHireItemCtrl::~CPCHireItemCtrl()
{
}


void CPCHireItemCtrl::Reset()
{
	m_ReqContainer.clear();
}


void CPCHireItemCtrl::RequestRemove(IVItItem* const in_pItem)
{
	if( in_pItem == NULL )
		return;

	REQUESTCONTAINERITOR itor = m_ReqContainer.find(in_pItem->IVItItem::GetUniqueIdentityNumV2());
	if( itor == m_ReqContainer.end() )
		return;

	m_ReqContainer.erase(itor);
}


void CPCHireItemCtrl::Init(CPC* in_cpOwnerPC)
{
	m_cpMyOwnerPC = in_cpOwnerPC;
}


DWORD CPCHireItemCtrl::GetNexCheckTime(const time_t in_CurDate, const DWORD in_CurTime, const IVItItem* const in_pItem) const
{
	time_t ExpireDate = in_pItem->IVItItem::GetHireExpireDate();
	if( in_CurDate >= ExpireDate )
		return in_CurTime; // already expired

	time_t Delta = ExpireDate - in_CurDate;
	if( Delta <= 7200 )
	{
		if( Delta > 3600 )
			Delta -= 3600;
		else
		if( Delta > 60 )
			Delta -= 60;
		else
		if( Delta > 10 )
			Delta -= 10;

		return in_CurTime + 1000 * Delta;
	}
	else
	{
		int div = rand() % 10;
		if( div < 1 )
			div = 1;
		return in_CurTime + 7200000 - 600000 / div;
	}
}


void CPCHireItemCtrl::RequestAdd(const enumInventoryType in_InventoryType, IVItItem* in_pItem)
{
	if( in_pItem == NULL || in_pItem->IVItItem::GetHireExpireDate() <= 0 || in_pItem->IVItItem::GetUniqueIdentityNumV2() <= 0 )
		return;

	if( in_pItem->GetType() == INVENTORYITEMTYPE_QUESTITEM )
		return;

	REQUESTCONTAINERITOR itor = m_ReqContainer.find(in_pItem->IVItItem::GetUniqueIdentityNumV2());
	if( itor == m_ReqContainer.end() )
	{
		m_ReqContainer.insert(std::pair<const __int64,CRequest>(in_pItem->IVItItem::GetUniqueIdentityNumV2(), CRequest(in_InventoryType, this->CPCHireItemCtrl::GetNexCheckTime(time(NULL), timeGetTime(), in_pItem))));
		
	}
	else
	{
		itor->second.m_InventoryType = in_InventoryType;
		itor->second.m_RequestCheckTime = this->CPCHireItemCtrl::GetNexCheckTime(time(NULL), timeGetTime(), in_pItem);
	}
}


bool CPCHireItemCtrl::RequestProcess(const __int64 in_ItemUID, CRequest& in_Request)
{
	IVItItem* pItem = m_cpMyOwnerPC->CPC::SearchItemByUniqueIdentityNum(in_Request.m_InventoryType, in_ItemUID);
	if( pItem == NULL )
		return true;

	time_t CurDate = time(NULL);
	time_t ExpireDate = pItem->IVItItem::GetHireExpireDate();
	DWORD CurTime = timeGetTime();

	if( CurDate > ExpireDate )
	{
		CITP* pITP = g_itpMgr.CITPMgr::GetITP(pItem->InventoryItem::GetID());
		if( pITP == NULL )
			return true;

		int RemainSecond = ExpireDate - CurDate;
		if( RemainSecond >= 0 && RemainSecond < 120 )
		{
			PACKET_ZC_CASH_TIME_COUNTER outpacket;
			outpacket.PacketType = HEADER_ZC_CASH_TIME_COUNTER;
			outpacket.ITID = pItem->InventoryItem::GetID();
			outpacket.RemainSecond = RemainSecond;
			m_cpMyOwnerPC->Send(sizeof(outpacket), (char*)&outpacket);
		}

		DWORD NextCheckTime = this->CPCHireItemCtrl::GetNexCheckTime(CurDate, CurTime, pItem);
		if( in_Request.m_RequestCheckTime + 60000 >= NextCheckTime )
			++in_Request.m_ErrorCount;

		if( in_Request.m_ErrorCount > 10 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "aid=%d itname=%s hire expire date=%d cur date=%d cur time=%d next check time=%d", m_cpMyOwnerPC->GetAccountID(), pITP->m_name, pItem->IVItItem::GetHireExpireDate(), CurDate, CurTime, NextCheckTime);
			return true;
		}

		in_Request.m_RequestCheckTime = NextCheckTime;
		return false;
	}

	if( in_Request.m_InventoryType == INVENTORYITEMTYPE_ITEM )
	{
		if( g_itpMgr.CITPMgr::GetITP(pItem->InventoryItem::GetID()) != NULL )
		{
			Request request;
			request.Request::SetID(RT_HIREITEM_RETURN);
			request.par1 = pItem->IVItItem::GetIndex();
			m_cpMyOwnerPC->CPC::OnDispatchClientRequest(&request);
		}
		return true;
	}
	else
	if( in_Request.m_InventoryType == INVENTORYITEMTYPE_MONEYITEM )
	{
		if( g_itpMgr.CITPMgr::GetITP(pItem->InventoryItem::GetID()) != NULL )
		{
			Request request;
			request.Request::SetID(RT_REQ_TAKEOFFEQUIP);
			request.par1 = pItem->IVItItem::GetIndex();
			m_cpMyOwnerPC->CPC::OnDispatchClientRequest(&request);
			m_cpMyOwnerPC->CPC::CheckWeaponState();
		}
		return false;
	}

	return true;
}


void CPCHireItemCtrl::Process()
{
	if( m_cpMyOwnerPC->CPC::IsValid() != TRUE )
		return;

	DWORD CurTime = timeGetTime();

	for( REQUESTCONTAINERITOR itor = m_ReqContainer.begin(); itor != m_ReqContainer.end(); )
	{
		if( CurTime >= itor->second.m_RequestCheckTime && this->CPCHireItemCtrl::RequestProcess(itor->first, itor->second) == true )
		{
			itor = m_ReqContainer.erase(itor);
		}
		else
		{
			++itor;
		}
	}
}
