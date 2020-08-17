#include "Enum.h"
#include "PC.h"
#include "PCItem.h"
#include "Common/Packet.h"
#include "Player/Inventory/CIVItItem.h"
#include "shared/NCriticalErrorLog.h"


struct SLOTINFO
{
	/* this+0 */ unsigned short slot[8];
};


struct EQUIPMENT_ITEMINFO_PC
{
	/* this+ 0 */ unsigned short ITID;
	/* this+ 2 */ SLOTINFO slot;
	/* this+18 */ unsigned char wearState;
};


struct NORMAL_ITEMINFO_PC
{
	/* this+ 0 */ unsigned short ITID;
	/* this+ 2 */ short count;
	/* this+ 4 */ SLOTINFO slot;
};


CPCItem::CPCItem()
{
}


CPCItem::~CPCItem()
{
}


void CPCItem::Init()
{
	m_pc = NULL;
	m_equipedSPItem.clear();
	m_isCombination.clear();
}


void CPCItem::SetMyOwner(CPC* pc)
{
	m_pc = pc;
}


BOOL CPCItem::ParseItem(const char* buf, short len)
{
	return FALSE;
	//TODO
	/*
	unsigned short type;
	memcpy_s(&type, sizeof(type), buf, sizeof(unsigned short));
	if( type == 1 || type == 2 || type == 3 || type == 4 )
		return FALSE;

	for( short count = 0; count < len; ++count )
	{
		const char* p = &buf[count];

		unsigned short ITID;
		memcpy_s(&ITID, sizeof(ITID), p, sizeof(unsigned short));
		if( ITID == 0 )
			break;

		CITP* itp = g_itpMgr.CITPMgr::GetITP(type);
		if( itp == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Parse Item Fail");
			m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return FALSE;
		}

		if( itp->IsApparel() )
		{
			EQUIPMENT_ITEMINFO_PC eItem;
			memcpy_s(&eItem, sizeof(eItem), p, sizeof(EQUIPMENT_ITEMINFO_PC));
			count += sizeof(EQUIPMENT_ITEMINFO_PC);

			IVItItem ivitItem;
			ivitItem.InventoryItem::SetID(eItem.ITID);
			ivitItem.IVItItem::SetCount(1);
			m_pc->m_pcitemInventoryMgr.m_bodyItem.Add(&ivitItem, 0, TRUE);
		}
		else
		{
			NORMAL_ITEMINFO_PC nItem;
			memcpy_s(&nItem, sizeof(nItem), p, sizeof(NORMAL_ITEMINFO_PC));
			count += sizeof(NORMAL_ITEMINFO_PC);

			IVItItem ivitItem;
			ivitItem.InventoryItem::SetID(nItem.ITID);
			ivitItem.IVItItem::SetCount(nItem.count);
			m_pc->m_pcitemInventoryMgr.m_bodyItem.Add(&ivitItem, 0, TRUE);
		}
	}

	return TRUE;
	*/
}


BOOL CPCItem::ParseStoredItem(const char* buf, short len)
{
	return FALSE;
	//TODO
	/*
	unsigned short type;
	memcpy_s(&type, sizeof(type), buf, sizeof(unsigned short));
	if( type == 1 || type == 2 || type == 3 || type == 4 )
		return FALSE;

	for( short count = 0; count < len; ++count )
	{
		const char* p = &buf[count];

		unsigned short ITID;
		memcpy_s(&ITID, sizeof(ITID), p, sizeof(unsigned short));

		CITP* itp = g_itpMgr.CITPMgr::GetITP(ITID);
		if( itp == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Parse Item");
			m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return FALSE;
		}

		if( itp->IsApparel() )
		{
			EQUIPMENT_ITEMINFO_PC eItem;
			memcpy_s(&eItem, sizeof(eItem), p, sizeof(EQUIPMENT_ITEMINFO_PC));
			count += sizeof(EQUIPMENT_ITEMINFO_PC);

			IVItItem ivitItem;
			ivitItem.InventoryItem::SetID(eItem.ITID);
			ivitItem.IVItItem::SetCount(1);
			m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::Add(&ivitItem, 2, 0, 0, 0);
		}
		else
		{
			NORMAL_ITEMINFO_PC nItem;
			memcpy_s(&nItem, sizeof(nItem), p, sizeof(NORMAL_ITEMINFO_PC));
			count += sizeof(NORMAL_ITEMINFO_PC);

			IVItItem ivitItem;
			ivitItem.InventoryItem::SetID(nItem.ITID);
			ivitItem.IVItItem::SetCount(nItem.count);
			m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::Add(&ivitItem, 2u, 0, 0, 0);
		}
	}

	return TRUE;
	*/
}


BOOL CPCItem::ParseCartItem(const char* buf, short len)
{
	return FALSE;
	//TODO
	/*
	if( len == 0 )
	{
		PACKET_ZC_CART_NORMAL_ITEMLIST outpacket1;
		outpacket1.PacketType = HEADER_ZC_CART_NORMAL_ITEMLIST;
		outpacket1.Length = sizeof(outpacket1) + len;
		m_pc->Send(outpacket1.Length, (char*)&outpacket1);
		return TRUE;
	}

	unsigned short type;
	memcpy_s(&type, sizeof(type), buf, sizeof(unsigned short));
	if( type == 1 || type == 2 || type == 3 || type == 4 || type == 5 )
		return FALSE;

	for( short count = 0; count < len; ++count )
	{
		const char* p = &buf[count];

		unsigned short ITID;
		memcpy_s(&ITID, sizeof(ITID), p, sizeof(unsigned short));

		CITP* itp = g_itpMgr.CITPMgr::GetITP(ITID);
		if( itp == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Parse Item Fail");
			m_pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return FALSE;
		}

		if( itp->IsApparel() )
		{
			EQUIPMENT_ITEMINFO_PC eItem;
			memcpy_s(&eItem, sizeof(eItem), p, sizeof(EQUIPMENT_ITEMINFO_PC));
			count += sizeof(EQUIPMENT_ITEMINFO_PC);

			IVItItem ivitItem;
			ivitItem.InventoryItem::SetID(eItem.ITID);
			ivitItem.IVItItem::SetCount(1);
			m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::Add(&ivitItem, 1, 0, 0, 0);
		}
		else
		{
			NORMAL_ITEMINFO_PC nItem;
			memcpy_s(&nItem, sizeof(nItem), p, sizeof(NORMAL_ITEMINFO_PC));
			count += sizeof(NORMAL_ITEMINFO_PC);

			IVItItem ivitItem;
			ivitItem.InventoryItem::SetID(nItem.ITID);
			ivitItem.IVItItem::SetCount(nItem.count);
			m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::Add(&ivitItem, 1, 0, 0, 0);
		}
	}

	return TRUE;
	*/
}


void CPCItem::CheckStateSpecialItem() // 239-289
{
	//TODO
}


BOOL CPCItem::IsEquipedSPItem(unsigned long ID)
{
	unsigned short ITID = static_cast<unsigned short>(ID);

	std::map<unsigned short,unsigned short>::const_iterator it = m_equipedSPItem.find(ITID);
	return ( it != m_equipedSPItem.end() );
}


void CPCItem::CHK_CompleteCombination() // 301-329
{
	//TODO
}


void CPCItem::CHK_ReleaseCombination() // 332-361
{
	//TODO
}


void CPCItem::OnEquipedSpecialITM(unsigned long itmID)
{
	unsigned short ITID = static_cast<unsigned short>(itmID);

	std::map<unsigned short,unsigned short>::iterator it = m_equipedSPItem.find(ITID);
	if( it == m_equipedSPItem.end() )
	{
		m_equipedSPItem[ITID] = 1;
	}
	else
	{
		++it->second;
	}

	this->CPCItem::CHK_CompleteCombination();
}


void CPCItem::OnTakeOffSpecialITM(unsigned long itmID)
{
	unsigned short ITID = static_cast<unsigned short>(itmID);

	std::map<unsigned short,unsigned short>::iterator it = m_equipedSPItem.find(ITID);
	if( it != m_equipedSPItem.end() )
	{
		--it->second;
		if( it->second == 0 )
			m_equipedSPItem.erase(it);
	}

	this->CPCItem::CHK_ReleaseCombination();
}


void CPCItem::RefreshEquipItem()
{
	//TODO
	/*
	static const unsigned long location[] = {
		LOCATION_HEAD,
		LOCATION_BODY,
		LOCATION_LARM,
		LOCATION_RARM,
		LOCATION_ROBE,
		LOCATION_SHOES,
		LOCATION_ACCESSORY1,
		LOCATION_ACCESSORY2,
		LOCATION_HEAD2,
		LOCATION_HEAD3,
		LOCATION_NOTHING
	};

	unsigned long AID = m_pc->GetAccountID();
	std::vector<unsigned long> itemList; // NOTE: unused

	for( int index = 0; location[index] != 0; ++index )
	{
		IVItEquipItem* item = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedItem(location[index]);
		if( item == NULL )
			continue;

		unsigned short ITID = item->InventoryItem::GetID();
		g_specialItmMgr.CSpecialItemMgr::SendMsg(ITID, 4, AID);
		g_specialItmMgr.CSpecialItemMgr::SendMsg(ITID, 2, AID);

		EQUIPSLOTINFO* slots = item->IVItItem::GetSlotInfo();
		if( slots == NULL )
			continue;

		if( slots->info[0] == 255 || slots->info[0] == 254 )
			continue;

		for( int slot = 0; slot < countof(slots->info); ++slot )
		{
			unsigned short slotITID = slots->info[slot];
			if( slotITID == 0 )
				continue;

			g_specialItmMgr.CSpecialItemMgr::SendMsg(slotITID, 4, AID);
			g_specialItmMgr.CSpecialItemMgr::SendMsg(slotITID, 2, AID);
		}
	}
	*/
}


int CPCItem::GetCombinationItemCount()
{
	return 0;
	//TODO
}
