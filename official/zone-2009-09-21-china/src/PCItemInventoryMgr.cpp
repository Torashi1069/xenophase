#include "CharacterMgr.h"
#include "CItem.hpp"
#include "ItemLog.h"
#include "CITP.hpp"
#include "CITPMgr.hpp"
#include "PCItemInventoryMgr.h"
#include "PC.h"
#include "CSpecialItemMgr.hpp"
#include "zoneprocess.h"
#include "Common/Packet.h"
#include "globals.hpp"
#include "struct.hpp"
#include "shared.h" // Trace


CPCItemInventoryMgr::CPCItemInventoryMgr(void)
{
}


CPCItemInventoryMgr::~CPCItemInventoryMgr(void)
{
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned char* out_pBuffer, const int in_MaxBytes)> CPCItemInventoryMgr::_GetBodyItemDBFormat(SERVER, "CPCItemInventoryMgr::GetBodyItemDBFormat");
int CPCItemInventoryMgr::GetBodyItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes)
{
	return (this->*_GetBodyItemDBFormat)(out_pBuffer, in_MaxBytes);

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned char* out_pBuffer, const int in_MaxBytes)> CPCItemInventoryMgr::_GetStoreItemDBFormat(SERVER, "CPCItemInventoryMgr::GetStoreItemDBFormat");
int CPCItemInventoryMgr::GetStoreItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes)
{
	return (this->*_GetStoreItemDBFormat)(out_pBuffer, in_MaxBytes);

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned char* out_pBuffer, const int in_MaxBytes)> CPCItemInventoryMgr::_GetCartItemDBFormat(SERVER, "CPCItemInventoryMgr::GetCartItemDBFormat");
int CPCItemInventoryMgr::GetCartItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes)
{
	return (this->*_GetCartItemDBFormat)(out_pBuffer, in_MaxBytes);

	//TODO
}


//hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_StoreItemReset(SERVER, "CPCItemInventoryMgr::StoreItemReset");
void CPCItemInventoryMgr::StoreItemReset(void) // line ???
{
//	return (this->*_StoreItemReset)();

	m_storeItem.Reset();
}


//hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_IsCartOn(SERVER, "CPCItemInventoryMgr::IsCartOn");
int CPCItemInventoryMgr::IsCartOn(void)
{
//	return (this->*_IsCartOn)();

	return m_cartItem.m_isFirstCartOn;
}


hook_method<void (CPCItemInventoryMgr::*)(Request* request)> CPCItemInventoryMgr::_OnMediatorRequest(SERVER, "CPCItemInventoryMgr::OnMediatorRequest");
void CPCItemInventoryMgr::OnMediatorRequest(Request* request)
{
	return (this->*_OnMediatorRequest)(request);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(Request* request)> CPCItemInventoryMgr::_OnDispatchClientRequest(SERVER, "CPCItemInventoryMgr::OnDispatchClientRequest");
void CPCItemInventoryMgr::OnDispatchClientRequest(Request* request)
{
	return (this->*_OnDispatchClientRequest)(request);
/*
	//TODO
	switch ( request->m_requestID )
	{
	case RT_HIREITEM_RETURN:
//		this->CPCItemInventoryMgr::OnHireItemReturn(LOWORD(request->par1));
	break;
	case RT_REQ_WEAREQUIP:
//		this->CPCItemInventoryMgr::OnWearItem(LOWORD(request->par1), LOWORD(request->par2));
	break;
	case RT_REQ_TAKEOFFEQUIP:
//		this->CPCItemInventoryMgr::OnTakeOffEquip(LOWORD(request->par1));
	break;
	case RT_REQ_PICKUPITEM:
		this->CPCItemInventoryMgr::OnPickUpItem(request->par1);
	break;
	case RT_REQ_THROWITEM:
//		if ( !CPCItemInventoryMgr::OnThrowItem(LOWORD(request->par1), LOWORD(request->par2), 0) )
//			CPC::NotifyItemThrowed(this->m_owner, LOWORD(request->par1), 0);
	break;
	case RT_REQ_USEITEM:
//		this->CPCItemInventoryMgr::OnUseItem(LOWORD(request->par1), request->par2);
	break;
	case RT_RESET_EXCHANGEITEM:
//		(*((void (__thiscall **)(_DWORD))this->m_exchangeItem.baseclass_0.baseclass_0.vtable + 11))(&this->m_exchangeItem);
	break;
	case RT_RESET_MCSTORE:
//		(*((void (__thiscall **)(_DWORD))this->m_mcStoreItem.baseclass_0.baseclass_0.vtable + 11))(&this->m_mcStoreItem);
	break;
	default:
		return;
	}
*/
}


hook_method<IVItItem* (CPCItemInventoryMgr::*)(IVItItem* item, unsigned long type, unsigned short desPos, int IsClientNotified, int IsFroceInsert)> CPCItemInventoryMgr::_Add(SERVER, "CPCItemInventoryMgr::Add");
IVItItem* CPCItemInventoryMgr::Add(IVItItem* item, unsigned long type, unsigned short desPos, int IsClientNotified, int IsFroceInsert)
{
	return (this->*_Add)(item, type, desPos, IsClientNotified, IsFroceInsert);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(IVItItem* item)> CPCItemInventoryMgr::_NotifyPickUpToParty(SERVER, "CPCItemInventoryMgr::NotifyPickUpToParty");
void CPCItemInventoryMgr::NotifyPickUpToParty(IVItItem* item)
{
	return (this->*_NotifyPickUpToParty)(item);

	if( m_owner->m_characterInfo.GroupID == 0 )
		return;

	if( item == NULL )
		return;

	CITP* v3 = g_itpMgr->CITPMgr::GetITP(item->m_ID);
	if( v3 == NULL )
		return;

	if( !v3->IsPickUpNotifyParty() )
		return;

	PACKET_ZC_ITEM_PICKUP_PARTY outpacket;
	outpacket.PacketType = HEADER_ZC_ITEM_PICKUP_PARTY;
	outpacket.accountID = m_owner->GetAccountID();
	outpacket.ITID = item->m_ID;
	outpacket.IsIdentified = item->m_isIdentified;
	if( item->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
	{
		outpacket.IsDamaged = ((IVItEquipItem *)item)->m_isDamaged;
		outpacket.refiningLevel = ((IVItEquipItem *)item)->IVItEquipItem::GetRefiningLevel();
		outpacket.slot = item->m_slotInfo;
	}
	else
	{
		outpacket.IsDamaged = 0;
		outpacket.refiningLevel = 0;
		outpacket.slot = item->m_slotInfo;
	}
	outpacket.location = v3->GetLocation(m_owner->m_characterInfo.job);
	outpacket.type = (unsigned char)v3->GetType();

	m_owner->CPC::SendPacketToPartyInMap(sizeof(outpacket), (char *)&outpacket, 1);
}


hook_method<static int (__cdecl *)(CommonItemInfo* item, char* buf, int len)> CPCItemInventoryMgr::_DBValueParser(SERVER, "CPCItemInventoryMgr::DBValueParser");
int CPCItemInventoryMgr::DBValueParser(CommonItemInfo* item, char* buf, int len)
{
	return (_DBValueParser)(item, buf, len);

	//TODO
}


hook_method<PASERRET::enumError (CPCItemInventoryMgr::*)(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType)> CPCItemInventoryMgr::_Parse(SERVER, "CPCItemInventoryMgr::Parse");
PASERRET::enumError CPCItemInventoryMgr::Parse(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType)
{
	return (this->*_Parse)(in_pRequest, in_bNotify, in_bUseZip, in_bUseItemType);

	//TODO
}


hook_method<PASERRET::enumError (CPCItemInventoryMgr::*)(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType)> CPCItemInventoryMgr::_ParseV4(SERVER, "CPCItemInventoryMgr::ParseV4");
PASERRET::enumError CPCItemInventoryMgr::ParseV4(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType)
{
	return (this->*_ParseV4)(in_pRequest, in_bNotify, in_bUseZip, in_bUseItemType);

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(Request* request)> CPCItemInventoryMgr::_Save(SERVER, "CPCItemInventoryMgr::Save");
int CPCItemInventoryMgr::Save(Request* request)
{
	return (this->*_Save)(request);

	//TODO
}


hook_method<IVItItem* (CPCItemInventoryMgr::*)(const enum enumInventoryType in_InventoryType, const __int64 in_UID)> CPCItemInventoryMgr::_SearchItemByUniqueIdentityNum(SERVER, "CPCItemInventoryMgr::SearchItemByUniqueIdentityNum");
IVItItem* CPCItemInventoryMgr::SearchItemByUniqueIdentityNum(const enum enumInventoryType in_InventoryType, const __int64 in_UID)
{
	return (this->*_SearchItemByUniqueIdentityNum)(in_InventoryType, in_UID);

	//TODO
}


hook_method<IVItItem* (CPCItemInventoryMgr::*)(unsigned long type, short index)> CPCItemInventoryMgr::_SearchItem(SERVER, "CPCItemInventoryMgr::SearchItem");
IVItItem* CPCItemInventoryMgr::SearchItem(unsigned long type, short index)
{
	return (this->*_SearchItem)(type, index);

	//TODO
}


hook_method<IVItItem* (CPCItemInventoryMgr::*)(unsigned long type, unsigned short ITID)> CPCItemInventoryMgr::_SearchItemByID(SERVER, "CPCItemInventoryMgr::SearchItemByID");
IVItItem* CPCItemInventoryMgr::SearchItemByID(unsigned long type, unsigned short ITID)
{
	return (this->*_SearchItemByID)(type, ITID);

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned long type, short index, short count)> CPCItemInventoryMgr::_DeleteItem(SERVER, "CPCItemInventoryMgr::DeleteItem");
int CPCItemInventoryMgr::DeleteItem(unsigned long type, short index, short count)
{
	return (this->*_DeleteItem)(type, index, count);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(const unsigned long in_Type)> CPCItemInventoryMgr::_NotifyItemInfo(SERVER, "CPCItemInventoryMgr::NotifyItemInfo");
void CPCItemInventoryMgr::NotifyItemInfo(const unsigned long in_Type)
{
	return (this->*_NotifyItemInfo)(in_Type);

	int nNormalSize;
	int nEquipSize;
	int s1, s2;

	char NormalItemBuffer[16305];
	char EquipItemBuffer[16305];
	memset(NormalItemBuffer, 0, sizeof(NormalItemBuffer));
	memset(EquipItemBuffer, 0, sizeof(EquipItemBuffer));

	switch( in_Type )
	{
	case BODY:
	{
		PACKET_ZC_NORMAL_ITEMLIST3& packet = *(PACKET_ZC_NORMAL_ITEMLIST3*)NormalItemBuffer;
		packet.PacketType = HEADER_ZC_NORMAL_ITEMLIST3;
		s1 = m_bodyItem.CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(&NormalItemBuffer[4], 16300);
		s2 = m_equipedItem.CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(&NormalItemBuffer[4 + s1], 16300 - s1);
		nNormalSize = s1 + s2;

		PACKET_ZC_EQUIPMENT_ITEMLIST3& eqpacket = *(PACKET_ZC_EQUIPMENT_ITEMLIST3*)EquipItemBuffer;
		eqpacket.PacketType = HEADER_ZC_EQUIPMENT_ITEMLIST3;
		s1 = m_bodyItem.CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(&EquipItemBuffer[4], 16300, 1);
		s2 = m_equipedItem.CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(&EquipItemBuffer[4 + s1], 16300 - s1, 0);
		nEquipSize = s1 + s2;
	}
	break;
	case CART:
	{
		PACKET_ZC_CART_NORMAL_ITEMLIST3& packet = *(PACKET_ZC_CART_NORMAL_ITEMLIST3*)NormalItemBuffer;
		packet.PacketType = HEADER_ZC_CART_NORMAL_ITEMLIST3;
		nNormalSize = m_cartItem.CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(&NormalItemBuffer[4], 16300);

		PACKET_ZC_CART_EQUIPMENT_ITEMLIST3& eqpacket = *(PACKET_ZC_CART_EQUIPMENT_ITEMLIST3*)EquipItemBuffer;
		eqpacket.PacketType = HEADER_ZC_CART_EQUIPMENT_ITEMLIST3;
		nEquipSize = m_storeItem.CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(&EquipItemBuffer[4], 16300, 0);
	}
	break;
	case STORE:
	{
		PACKET_ZC_STORE_NORMAL_ITEMLIST3& packet = *(PACKET_ZC_STORE_NORMAL_ITEMLIST3*)NormalItemBuffer;
		packet.PacketType = HEADER_ZC_STORE_NORMAL_ITEMLIST3;
		nNormalSize = m_storeItem.CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(&NormalItemBuffer[4], 16300);

		PACKET_ZC_STORE_EQUIPMENT_ITEMLIST3& eqpacket = *(PACKET_ZC_STORE_EQUIPMENT_ITEMLIST3*)EquipItemBuffer;
		eqpacket.PacketType = HEADER_ZC_STORE_EQUIPMENT_ITEMLIST3;
		nEquipSize = m_cartItem.CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(&EquipItemBuffer[4], 16300, 0);
	}
	break;
	default:
		return;
	break;
	}

	if( nNormalSize != 0 )
	{
		PACKET_ZC_NORMAL_ITEMLIST3& packet = *(PACKET_ZC_NORMAL_ITEMLIST3*)NormalItemBuffer;
		packet.Length = sizeof(packet) + nNormalSize;
		m_owner->CPC::Send(packet.Length, (char*)&packet);
	}

	if( nEquipSize != 0 )
	{
		PACKET_ZC_EQUIPMENT_ITEMLIST3& packet = *(PACKET_ZC_EQUIPMENT_ITEMLIST3*)EquipItemBuffer;
		packet.Length = sizeof(packet) + nEquipSize;
		m_owner->CPC::Send(packet.Length, (char*)&packet);
	}
}


hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_RefreshItemWeight(SERVER, "CPCItemInventoryMgr::RefreshItemWeight");
void CPCItemInventoryMgr::RefreshItemWeight(void)
{
	return (this->*_RefreshItemWeight)();

	//TODO
}


hook_method<bool (CPCItemInventoryMgr::*)(const int in_Length, const unsigned char* in_pData)> CPCItemInventoryMgr::_ParseDBFmtBodyItemData(SERVER, "CPCItemInventoryMgr::ParseDBFmtBodyItemData");
bool CPCItemInventoryMgr::ParseDBFmtBodyItemData(const int in_Length, const unsigned char* in_pData)
{
	return (this->*_ParseDBFmtBodyItemData)(in_Length, in_pData);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(short index, unsigned long AID)> CPCItemInventoryMgr::_OnUseItem(SERVER, "CPCItemInventoryMgr::OnUseItem");
void CPCItemInventoryMgr::OnUseItem(short index, unsigned long AID)
{
	return (this->*_OnUseItem)(index, AID);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(short index, unsigned short wearLocation)> CPCItemInventoryMgr::_OnWearItem(SERVER, "CPCItemInventoryMgr::OnWearItem");
void CPCItemInventoryMgr::OnWearItem(short index, unsigned short wearLocation)
{
	return (this->*_OnWearItem)(index, wearLocation);

	PACKET_ZC_REQ_WEAR_EQUIP_ACK outpacket;
	outpacket.PacketType = HEADER_ZC_REQ_WEAR_EQUIP_ACK;
	outpacket.index = index;
	outpacket.result = 1;

	if( m_owner->GetState() == 5 )
	{
		outpacket.result = 0;
		m_owner->CPC::Send(sizeof(outpacket), (char *)&outpacket);
		return;
	}

	IVItItem* v7 = m_bodyItem.CPCItemInventory::SearchItemByIndex(index);
	Trace("wearLocation A = %d *** \n", wearLocation);
	if ( !v7 )
	{
		Trace("없는 아이템 착용 요청. index:%d\n", index);
		outpacket.result = 0;
		m_owner->CPC::Send(sizeof(outpacket), (char *)&outpacket);
		return;
	}

	CITP* v9 = g_itpMgr->CITPMgr::GetITP(v7->m_ID);
	if( v9->GetType() == TYPE_ARMORTB )
		wearLocation = 257;

	if( m_equipedItem.CPCEquipedItemIV::IsEquipable(wearLocation, v7) == 0 )
	{
		if( m_owner->m_pcSkill.CPCSkill::GetSkillLevel(SKID_MB_B_EQUIP,0) != 0
		&&  !(wearLocation & 2) )
		{
			outpacket.result = 1;
			outpacket.wearLocation = wearLocation;

			this->CPCItemInventoryMgr::TakeOffEquip(wearLocation);
		}
		else
		if( m_owner->CPC::GetCategorySecondJob() == JT_SUPERNOVICE
		&&  m_owner->GetEffective(EFST_SOULLINK, 0)
		&&  m_owner->m_characterInfo.clevel >= 90
		&&  (wearLocation == 1 || wearLocation - 0x100 <= 0x7EFFu) )
		{
			outpacket.result = 1;
			outpacket.wearLocation = wearLocation;

			this->CPCItemInventoryMgr::TakeOffEquip(wearLocation);

		}
		else
		if( m_owner->CPC::GetCategorySecondJob() == JT_SUPERNOVICE
		&&  m_owner->GetEffective(EFST_SOULLINK, 0)
		&&  m_owner->m_characterInfo.clevel >= 96
		&&  v9->GetItemLevel() == 4
		&&  (v9->GetClass() == 1 || v9->GetClass() == 2 || v9->GetClass() == 6 || v9->GetClass() == 7 || v9->GetClass() == 8 || v9->GetClass() == 10 || v9->GetClass() == 23) )
		{
			outpacket.result = 1;
			outpacket.wearLocation = wearLocation;

			if( v9->GetType() != TYPE_BOTHHAND )
			{
				this->CPCItemInventoryMgr::TakeOffEquip(wearLocation);
			}
			else
			{
				this->CPCItemInventoryMgr::TakeOffEquip(0x20);
				this->CPCItemInventoryMgr::TakeOffEquip(2);
			}
		}
		else
		{
			outpacket.result = 0;

			if( m_owner->CPC::IsPetWearable(v7->m_ID) )
			{
				m_owner->CPC::OnUsePetAcc(v7->m_ID);
				return;
			}
		}
		
		if( outpacket.result != 1 )
		{
			m_owner->CPC::Send(sizeof(outpacket), (char *)&outpacket);
			return;
		}
	}
	else
	{
		switch( v9->GetType() )
		{
		case TYPE_BOW:
		case TYPE_BOTHHAND:
		case TYPE_GUN:
			wearLocation = v9->GetLocation(m_owner->m_characterInfo.job);
			break;
		case TYPE_ARROW:
		case TYPE_AMMO:
		case TYPE_THROWWEAPON:
		case TYPE_CANNONBALL:
		{
			m_owner->CPC::NotifyActionFailure(3u);
			wearLocation = 32768;
			IVItItem* v10 = m_bodyItem.Remove(index, v7->m_count);
			if( v10 )
			{
				m_equipedItem.Add(v10, wearLocation, 1);
				m_owner->UpdateParameterValue(193, 0);
				m_owner->CPC::NotifyParameter(0x29u, m_owner->CPC::GetAttPowerOnClient());
				m_owner->CPC::NotifyArrowEquiped(index);
				return;
			}
			return;
		}
		default:
			break;
		}

		Trace("wearLocation B = %d *** \n", wearLocation);
		outpacket.result = 1;
		outpacket.wearLocation = wearLocation;
	}

	IVItItem* v14 = m_bodyItem.Remove(index, 1);
	if( v14 == NULL )
	{
		outpacket.result = 0;
		m_owner->CPC::Send(sizeof(outpacket), (char *)&outpacket);
		return;
	}

	Trace("wearLocation C = %d *** \n", wearLocation);

	m_equipedItem.Add(v14, wearLocation, 1);

	if( v9->GetType() == TYPE_ARMOR || v9->GetType() == TYPE_ARMORTM || v9->GetType() == TYPE_ARMORTB || v9->GetType() == TYPE_ARMORMB || v9->GetType() == TYPE_ARMORTMB )
	{
		m_owner->CPC::NotifyParameter(VAR_ITEMDEFPOWER, 0);
		m_owner->CPC::NotifyParameter(VAR_MDEFPOWER, 0);
		m_owner->CPC::NotifyParameter(VAR_PLUSDEFPOWER, 0);
	}
	else
	{
		m_owner->CPC::NotifyParameter(VAR_ATTPOWER, m_owner->CPC::GetAttPowerOnClient());
		m_owner->CPC::NotifyParameter(VAR_PLUSATTREFININGPOWEROFITEM, m_owner->CPC::GetRefiningAttPowerOnClient());
	}

	m_owner->UpdateParameterValue(VAR_ITEMPOWER, 0);
	m_owner->UpdateParameterValue(VAR_ITEMMAGICPOWER, 0);
	m_owner->UpdateParameterValue(VAR_ITEMDEFPOWER, 0);
	m_owner->UpdateParameterValue(VAR_MDEFPOWER, 0);

	m_owner->CPC::Send(sizeof(outpacket), (char *)&outpacket);
}


hook_method<void (CPCItemInventoryMgr::*)(unsigned long ITAID)> CPCItemInventoryMgr::_OnPickUpItem(SERVER, "CPCItemInventoryMgr::OnPickUpItem");
void CPCItemInventoryMgr::OnPickUpItem(unsigned long ITAID)
{
	return (this->*_OnPickUpItem)(ITAID);

	if( !this->m_owner->CPC::IsPickable() )
	{
		this->CPCItemInventoryMgr::NotifyAckAddItemToBody(1u, NULL);
		return;
	}

	CItem* item = (CItem*) g_characterMgr->CCharacterMgr::FindCharacter(ITAID, ITEM_TYPE);
	if( !item )
		return;
	
	if( item->m_pickableType == 1 && item->m_pickablePARTYID != 0 )
	{
		int party_id; // shares stack with 'isdamaged'
		m_owner->GetParameterValue(VAR_GROUPID, party_id);
		if ( party_id != item->m_pickablePARTYID )
		{
			this->CPCItemInventoryMgr::NotifyAckAddItemToBody(6u, NULL);
			return;
		}
	}
	else
	{
		unsigned int v6 = m_owner->GetAccountID();
		if( !item->CItem::IsPickUpable(v6) )
		{
			this->CPCItemInventoryMgr::NotifyAckAddItemToBody(6u, NULL);
			return;
		}
	}

	if( this->m_owner->m_characterInfo.PartyItemDivisionRule && this->m_owner->m_groupMember.size() > 1 )
	{
		this->CPCItemInventoryMgr::RandomDivision(item);
		return;
	}

	int myXpos;
	int myYpos;
	int otherXPos;
	int otherYPos;
	int mapID;
	item->GetParameterValue(VAR_CURXPOS, otherXPos);
	item->GetParameterValue(VAR_CURYPOS, otherYPos);
	m_owner->GetParameterValue(VAR_CURXPOS, myXpos);
	m_owner->GetParameterValue(VAR_CURYPOS, myYpos);
	item->GetParameterValue(VAR_MAPID, mapID);

	if( !(mapID == this->m_owner->m_characterInfo.mapID && abs(otherXPos - myXpos) < 5 && abs(otherYPos - myYpos) < 5) )
		return;

	if( !g_itpMgr->CITPMgr::GetITP(item->GetITID()) )
		return;

	IVItItem* ivit = this->AllocInventoryItem(item->GetITID(), item->m_itemInfo.count);
	if( !ivit )
		return;

	int identifyflag;
	int slot1;
	int slot2;
	int slot3;
	int slot4;
	item->GetParameterValue(VAR_ISIDENTIFIED, identifyflag);
	ivit->m_isIdentified = ( identifyflag != 0 );
	item->GetParameterValue(VAR_ITEM_SLOT1, slot1);
	item->GetParameterValue(VAR_ITEM_SLOT2, slot2);
	item->GetParameterValue(VAR_ITEM_SLOT3, slot3);
	item->GetParameterValue(VAR_ITEM_SLOT4, slot4);
	ivit->m_slotInfo.info[0] = slot1;
	ivit->m_slotInfo.info[1] = slot2;
	ivit->m_slotInfo.info[2] = slot3;
	ivit->m_slotInfo.info[3] = slot4;
	ivit->IVItItem::SetUniqueIdentityNumV2(item->m_itemInfo.unique_identity_numberV2);
	ivit->IVItItem::SetHireExpireDate(item->m_itemInfo.hire_expire_date);

	if( ivit->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
	{
		int isdamaged;
		int refininglevel;
		item->GetParameterValue(VAR_ISDAMAGED, isdamaged);
		item->GetParameterValue(VAR_REFININGLEVEL, refininglevel);
		((IVItEquipItem*)ivit)->m_isDamaged = ( isdamaged != 0 );
		((IVItEquipItem*)ivit)->m_refiningLevel = refininglevel;
	}

	if( !this->CPCItemInventoryMgr::Add(ivit, 0, 0, 1, 0) )
	{
		this->CPCItemInventoryMgr::FreeInventoryItem((InventoryItem *)ivit);
		return;
	}

	this->CPCItemInventoryMgr::NotifyPickUpToParty(ivit);
	g_itemLog->CItemLog::AddItemLog(1, this->m_owner, NULL, ivit, 0, ivit->m_count, NULL);
	this->CPCItemInventoryMgr::RefreshItemWeight();

	// send item pickup animation
	PACKET_ZC_NOTIFY_ACT outpacket2;
	outpacket2.PacketType = HEADER_ZC_NOTIFY_ACT;
	outpacket2.startTime = timeGetTime();
	outpacket2.GID = m_owner->GetAccountID();
	outpacket2.targetGID = item->GetAccountID();
	outpacket2.action = 1;
	this->m_owner->CPC::Send(sizeof(outpacket2), (char *)&outpacket2);
	this->m_owner->CCharacter::MultiCast((char *)&outpacket2, sizeof(outpacket2));

	g_characterMgr->CCharacterMgr::RemoveCharacter(item);
}


hook_method<void (CPCItemInventoryMgr::*)(short index)> CPCItemInventoryMgr::_OnTakeOffEquip(SERVER, "CPCItemInventoryMgr::OnTakeOffEquip");
void CPCItemInventoryMgr::OnTakeOffEquip(short index)
{
	return (this->*_OnTakeOffEquip)(index);

	PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK outpacket;
	outpacket.PacketType = 172;
	outpacket.index = index;
	outpacket.result = 1;

	IVItItem* v3 = m_equipedItem.CPCItemInventory::SearchItemByIndex(index);
	if( v3 == NULL )
	{
		Trace("무기 벗기 실패:index:%d", index);
		outpacket.result = 0;
		m_owner->CPC::Send(sizeof(outpacket), (char *)&outpacket);
		return;
	}

	CITP* v5 = g_itpMgr->CITPMgr::GetITP(v3->m_ID);
	if( v5 == NULL )
	{
		Trace("무기 벗기 실패 ITID:%d", v3->m_ID);
		outpacket.result = 0;
		m_owner->CPC::Send(sizeof(outpacket), (char *)&outpacket);
		return;
	}

	if( !m_owner->CPC::IsMapPropertyBlockEquipItem(v3->m_ID) )
		g_specialItmMgr->CSpecialItemMgr::SendMsg(v3->m_ID, 4u, m_owner->GetAccountID());

	if( v3->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
	{
		for( int v9 = 0; v9 < 4; ++v9 )
		{
			unsigned short v10 = v3->m_slotInfo.info[0];
			if( v10 == 255 )
				break;
			if( v10 == 254 )
				break;

			unsigned short v11 = v3->m_slotInfo.info[v9];
			if( v11 != 0 && !m_owner->CPC::IsMapPropertyBlockEquipItem(v11) )
				g_specialItmMgr->CSpecialItemMgr::SendMsg(v3->m_slotInfo.info[v9], 4u, m_owner->GetAccountID());
		}
	}

	if( v3->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
	{
		outpacket.wearLocation = ((IVItEquipItem*)v3)->m_wearState;
		Trace("벗기 요청. index:%d, 위치:%d", v3->m_index, outpacket.wearLocation);

		if( outpacket.wearLocation & 2 )
		{
			if( m_owner->GetEffective(EFST_AURABLADE, 0) )
				m_owner->ResetEffective(EFST_AURABLADE, 0);
		}

		IVItItem* v14 = m_equipedItem.Remove(index, 1);
		m_bodyItem.Add(v14, 0, 0);
	}
	else
	if( v3->GetType() == INVENTORYITEMTYPE_NORMALARROWITEM )
	{
		outpacket.wearLocation = ((IVItNormalArrowItem*)v3)->m_wearState;

		IVItItem* v14 = m_equipedItem.Remove(index, v3->m_count);
		m_bodyItem.Add(v14, 0, 0);
	}

	if( v5->GetType() == TYPE_ARMOR
	||  v5->GetType() == TYPE_ARMORTM
	||  v5->GetType() == TYPE_ARMORTB
	||  v5->GetType() == TYPE_ARMORMB
	||  v5->GetType() == TYPE_ARMORTMB )
	{
		m_owner->CPC::NotifyParameter(VAR_ITEMDEFPOWER, 0);
		m_owner->CPC::NotifyParameter(VAR_MDEFPOWER, 0);
		m_owner->CPC::NotifyParameter(VAR_PLUSDEFPOWER, 0);
		if( v5->GetLocation(m_owner->m_characterInfo.job) == LOCATION_BODY )
			m_owner->UpdateParameterValue(VAR_ARMORPROPERTY, 0);
	}
	else
	{
		m_owner->CPC::NotifyParameter(VAR_ATTPOWER, m_owner->CPC::GetAttPowerOnClient());
		m_owner->CPC::NotifyParameter(VAR_PLUSATTREFININGPOWEROFITEM, m_owner->CPC::GetRefiningAttPowerOnClient());
	}

	m_owner->UpdateParameterValue(VAR_ITEMPOWER, 0);
	m_owner->UpdateParameterValue(VAR_ITEMMAGICPOWER, 0);
	m_owner->UpdateParameterValue(VAR_ITEMDEFPOWER, 0);
	m_owner->UpdateParameterValue(VAR_MDEFPOWER, 0);

	m_owner->CPC::Send(sizeof(outpacket), (char *)&outpacket);
}


hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_GetBodyItemWeight(SERVER, "CPCItemInventoryMgr::GetBodyItemWeight");
int CPCItemInventoryMgr::GetBodyItemWeight(void)
{
	return (this->*_GetBodyItemWeight)();

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned short id, int& value)> CPCItemInventoryMgr::_GetJustBodyItemCount(SERVER, "CPCItemInventoryMgr::GetJustBodyItemCount");
int CPCItemInventoryMgr::GetJustBodyItemCount(unsigned short id, int& value)
{
	return (this->*_GetJustBodyItemCount)(id, value);

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned short id, int& value)> CPCItemInventoryMgr::_GetJustEquipItemCount(SERVER, "CPCItemInventoryMgr::GetJustEquipItemCount");
int CPCItemInventoryMgr::GetJustEquipItemCount(unsigned short id, int& value)
{
	return (this->*_GetJustEquipItemCount)(id, value);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(int npcAID, int ITID, int count)> CPCItemInventoryMgr::_OnSetBodyItem(SERVER, "CPCItemInventoryMgr::OnSetBodyItem");
void CPCItemInventoryMgr::OnSetBodyItem(int npcAID, int ITID, int count)
{
	return (this->*_OnSetBodyItem)(npcAID, ITID, count);

	if( count < 0 )
		return;

	IVItItem* v5 = m_bodyItem.CPCItemInventory::SearchItemByID(ITID, false);
	if( v5 == NULL )
	{
		IVItItem aitem;
		aitem.m_ID = ITID;
		aitem.m_count = count;

		IVItItem* v8 = this->CPCItemInventoryMgr::Add(&aitem, 0, 0, 1, 0);
		if( v8 == NULL )
			return;

		g_itemLog->CItemLog::AddItemLog(11, m_owner, NULL, v8, 0, count, NULL);
	}
	else
	if( v5->m_count <= count )
	{
		IVItItem aitem;
		aitem.m_ID = ITID;
		aitem.m_count = count - v5->m_count;

		IVItItem* v10 = this->CPCItemInventoryMgr::Add(&aitem, 0, 0, 1, 0);
		if( v10 == NULL )
			return;

		g_itemLog->CItemLog::AddItemLog(11, m_owner, NULL, v10, 0, count - v5->m_count, NULL);
	}
	else
	{
		m_bodyItem.Delete(v5->m_index, v5->m_count - count);
		g_itemLog->CItemLog::AddItemLog(11, m_owner, NULL, v5, 0, v5->m_count - count, NULL);
	}
}


hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_CancelExchangeItem(SERVER, "CPCItemInventoryMgr::CancelExchangeItem");
void CPCItemInventoryMgr::CancelExchangeItem(void)
{
	return (this->*_CancelExchangeItem)();

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(unsigned long loc)> CPCItemInventoryMgr::_TakeOffEquip(SERVER, "CPCItemInventoryMgr::TakeOffEquip");
void CPCItemInventoryMgr::TakeOffEquip(unsigned long loc)
{
	return (this->*_TakeOffEquip)(loc);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_TakeOffAllEquip(SERVER, "CPCItemInventoryMgr::TakeOffAllEquip");
void CPCItemInventoryMgr::TakeOffAllEquip(void)
{
	return (this->*_TakeOffAllEquip)();

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_GetBodyItemWeightByPercent(SERVER, "CPCItemInventoryMgr::GetBodyItemWeightByPercent");
int CPCItemInventoryMgr::GetBodyItemWeightByPercent(void)
{
	return (this->*_GetBodyItemWeightByPercent)();

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned long type)> CPCItemInventoryMgr::_GetPlusPowerOfItem(SERVER, "CPCItemInventoryMgr::GetPlusPowerOfItem");
int CPCItemInventoryMgr::GetPlusPowerOfItem(unsigned long type)
{
	return (this->*_GetPlusPowerOfItem)(type);

	return m_equipedItem.CPCEquipedItemIV::GetPlusPowerOfItem(type);
}


IVItEquipItem* CPCEquipedItemIV::GetEquipedItem(unsigned long loc)
{
	switch( loc )
	{
	case LOCATION_HEAD      : return static_cast<IVItEquipItem*>(m_head);
	case LOCATION_BODY      : return static_cast<IVItEquipItem*>(m_body);
	case LOCATION_LARM      : return static_cast<IVItEquipItem*>(m_larm);
	case LOCATION_RARM      : return static_cast<IVItEquipItem*>(m_rarm);
	case LOCATION_ROBE      : return static_cast<IVItEquipItem*>(m_robe);
	case LOCATION_SHOES     : return static_cast<IVItEquipItem*>(m_shoes);
	case LOCATION_ACCESSORY1: return static_cast<IVItEquipItem*>(m_accessory1);
	case LOCATION_ACCESSORY2: return static_cast<IVItEquipItem*>(m_accessory2);
	case LOCATION_HEAD2     : return static_cast<IVItEquipItem*>(m_head2);
	case LOCATION_HEAD3     : return static_cast<IVItEquipItem*>(m_head3);
	default                 : return NULL;
	};
}


IVItItem* CPCItemInventoryMgr::GetEquipedArrow()
{
	return m_equipedItem.CPCEquipedItemIV::GetEquipedArrow();
}


IVItEquipItem* CPCItemInventoryMgr::GetEquipedItem(unsigned long loc)
{
	return m_equipedItem.CPCEquipedItemIV::GetEquipedItem(loc);
}


hook_method<void (CPCItemInventoryMgr::*)(unsigned short id)> CPCItemInventoryMgr::_ReqMakeArrow(SERVER, "CPCItemInventoryMgr::ReqMakeArrow");
void CPCItemInventoryMgr::ReqMakeArrow(unsigned short id)
{
	return (this->*_ReqMakeArrow)(id);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(const int in_Length, const unsigned char* in_pData)> CPCItemInventoryMgr::_ParseDBFmtStoreItemData(SERVER, "CPCItemInventoryMgr::ParseDBFmtStoreItemData");
void CPCItemInventoryMgr::ParseDBFmtStoreItemData(const int in_Length, const unsigned char* in_pData)
{
	return (this->*_ParseDBFmtStoreItemData)(in_Length, in_pData);

	if( this->CPCItemInventoryMgr::IsStoreOpen() )
		return;

	if( in_Length == -1 )
		return;

	m_storeItem.CPCStoreItemIV::SetStoreOpenFlag(TRUE);

	if( in_Length == 0 || in_Length == 2 )
	{
		PACKET_ZC_STORE_NORMAL_ITEMLIST outpacket;
		outpacket.PacketType = HEADER_ZC_STORE_NORMAL_ITEMLIST;
		outpacket.PacketLength = sizeof(outpacket) + 0;
		m_owner->CPC::Send(sizeof(outpacket), (char*)&outpacket);

		this->CPCItemInventoryMgr::NotifyStoreItemCountInfo();
		return;
	}

	if( !m_owner->m_pcItem.CPCItem::ParseStoredItem((const char*)in_pData, in_Length) )
	{
		m_storeItem.CPCStoreItemIV::SetStoreOpenFlag(FALSE);
		m_owner->AddErrorCount(".\\PCItemInventoryMgr.cpp", 1192, 4, timeGetTime());
		return;
	}

	Request request;
	request.Request::SetID(RT_STOREITEM_PARSING);
	request.par1 = (int)in_pData;
	request.par2 = (int)in_Length;

	if( this->CPCItemInventoryMgr::Parse(&request, false, false, false) != PASERRET::ERROR_NONE )
	{
		m_storeItem.CPCStoreItemIV::SetStoreOpenFlag(FALSE);
		m_owner->AddErrorCount(".\\PCItemInventoryMgr.cpp", 1192, 4, timeGetTime());
		return;
	}

	this->CPCItemInventoryMgr::NotifyItemInfo(STORE);
	this->CPCItemInventoryMgr::NotifyStoreItemCountInfo();
}


hook_method<bool (CPCItemInventoryMgr::*)(const int in_Length, const unsigned char* in_pData)> CPCItemInventoryMgr::_ParseDBFmtCartItemData(SERVER, "CPCItemInventoryMgr::ParseDBFmtCartItemData");
bool CPCItemInventoryMgr::ParseDBFmtCartItemData(const int in_Length, const unsigned char* in_pData)
{
	return (this->*_ParseDBFmtCartItemData)(in_Length, in_pData);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_NotifyStoreItemCountInfo(SERVER, "CPCItemInventoryMgr::NotifyStoreItemCountInfo");
void CPCItemInventoryMgr::NotifyStoreItemCountInfo(void)
{
	return (this->*_NotifyStoreItemCountInfo)();

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_CloseStore(SERVER, "CPCItemInventoryMgr::CloseStore");
void CPCItemInventoryMgr::CloseStore(void)
{
	return (this->*_CloseStore)();

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_IsStoreOpen(SERVER, "CPCItemInventoryMgr::IsStoreOpen");
int CPCItemInventoryMgr::IsStoreOpen(void)
{
	return (this->*_IsStoreOpen)();

	//TODO
}


/* hook_method<void (CPCItemInventoryMgr::*)(int len, char* buf)> CPCItemInventoryMgr::_OnReqOpenMCStore(SERVER, "CPCItemInventoryMgr::OnReqOpenMCStore");
void CPCItemInventoryMgr::OnReqOpenMCStore(int len, char* buf)
{
	return (this->*_OnReqOpenMCStore)(len, buf);

	//TODO
} */


hook_method<void (CPCItemInventoryMgr::*)(unsigned long AID)> CPCItemInventoryMgr::_NotifyItemInfoInMCStore(SERVER, "CPCItemInventoryMgr::NotifyItemInfoInMCStore");
void CPCItemInventoryMgr::NotifyItemInfoInMCStore(unsigned long AID)
{
	return (this->*_NotifyItemInfoInMCStore)(AID);

	char buf[1024];
	int count = 0;

	for( mystd::vector<IVItItem*>::iterator it = m_mcStoreItem.CPCItemInventory::GetDataBeginIterator(); it != m_mcStoreItem.CPCItemInventory::GetDataEndIterator(); ++it )
	{
		IVItItem* i = *it;

		CITP* itp = g_itpMgr->CITPMgr::GetITP(i->m_ID);
		if( itp == NULL )
			continue;

		PURCHASE_ITEM_FROMMC item;
		item.index = i->m_index;
		item.type = static_cast<unsigned char>(itp->GetType());
		item.price = m_mcStoreItem.CPCMCStoreItemIV::GetPrice(i->m_index);;
		item.IsIdentified = i->m_isIdentified;
		item.count = i->m_count;
		item.ITID = i->m_ID;

		if( i->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
		{
			item.IsDamaged = static_cast<IVItEquipItem*>(i)->m_isDamaged;
			item.refiningLevel = static_cast<IVItEquipItem*>(i)->IVItEquipItem::GetRefiningLevel();
			memcpy(&item.slot, static_cast<IVItEquipItem*>(i)->m_slotInfo.info, sizeof(item.slot));
		}
		else
		{
			item.IsDamaged = false;
			item.refiningLevel = 0;
			memcpy(&item.slot, i->m_slotInfo.info, sizeof(item.slot));
		}

		memcpy(&buf[count], &item, sizeof(item));
		count += sizeof(item);
	}

	PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC outpacket;
	outpacket.PacketType = HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC;
	outpacket.AID = m_owner->GetAccountID();
	outpacket.PacketLength = sizeof(outpacket) + count;
	g_characterMgr->CCharacterMgr::SendMsg(m_owner, AID, CM_SEND_PACKET, 8, (int)&outpacket, 0, 0);
	g_characterMgr->CCharacterMgr::SendMsg(m_owner, AID, CM_SEND_PACKET, count, (int)buf, 0, 0);
}


hook_method<void (CPCItemInventoryMgr::*)(unsigned long targetAID, int contentLength, char* buf)> CPCItemInventoryMgr::_PurchaseItemFromMCStore(SERVER, "CPCItemInventoryMgr::PurchaseItemFromMCStore");
void CPCItemInventoryMgr::PurchaseItemFromMCStore(unsigned long targetAID, int contentLength, char* buf)
{
	return (this->*_PurchaseItemFromMCStore)(targetAID, contentLength, buf);

	if( m_owner->GetEffective(EFST_NOACTION_WAIT, 0) )
		return;

	CPC* other = (CPC*) g_characterMgr->CCharacterMgr::FindCharacter(targetAID, PC_TYPE);
	if( other == NULL )
		return;

	int sumOfTotal = 0;

	for( int i = 0; i < contentLength; i += sizeof(CZ_PURCHASE_ITEM_FROMMC) )
	{
		CZ_PURCHASE_ITEM_FROMMC& content = ((CZ_PURCHASE_ITEM_FROMMC*)buf)[i];
		short count = content.count;
		short index = content.index;

		IVItItem* v8 = other->m_pcitemInventoryMgr.m_mcStoreItem.CPCItemInventory::SearchItemByIndex(index);
		if( v8 == NULL )
		{
			PACKET_ZC_PC_PURCHASE_RESULT_FROMMC packet;
			packet.PacketType = HEADER_ZC_PC_PURCHASE_RESULT_FROMMC;
			packet.index = index;
			packet.curcount = 0;
			packet.result = 4;
			m_owner->CPC::Send(sizeof(packet), (char*)&packet);
			continue;
		}

		if( count < 1 || count > v8->m_count )
		{
			PACKET_ZC_PC_PURCHASE_RESULT_FROMMC packet;
			packet.PacketType = HEADER_ZC_PC_PURCHASE_RESULT_FROMMC;
			packet.index = index;
			packet.curcount = v8->m_count;
			packet.result = 4;
			m_owner->CPC::Send(sizeof(packet), (char*)&packet);
			continue;
		}

		if( g_itpMgr->CITPMgr::GetITP(v8->m_ID) == NULL )
		{
			PACKET_ZC_PC_PURCHASE_RESULT_FROMMC packet;
			packet.PacketType = HEADER_ZC_PC_PURCHASE_RESULT_FROMMC;
			packet.index = index;
			packet.curcount = v8->m_count;
			packet.result = 4;
			m_owner->CPC::Send(sizeof(packet), (char*)&packet);
			continue;
		}

		int price = other->m_pcitemInventoryMgr.m_mcStoreItem.CPCMCStoreItemIV::GetPrice(index);
		int cost = count * price;

		if( (long long)(count * price) > INT_MAX || m_owner->m_characterInfo.money < cost || price > g_MaxZenyStore || cost < 0 )
		{
			PACKET_ZC_PC_PURCHASE_RESULT_FROMMC packet;
			packet.PacketType = HEADER_ZC_PC_PURCHASE_RESULT_FROMMC;
			packet.index = index;
		//	packet.curcount = 0; //FIXME: uninitialized
			packet.result = 1;
			m_owner->CPC::Send(sizeof(packet), (char*)&packet);
			continue;
		}

		sumOfTotal += cost;

		IVItItem* v17 = other->m_pcitemInventoryMgr.m_mcStoreItem.Remove(index, count);
		IVItItem* v14 = this->AllocInventoryItem(v17->m_ID, 1);
		if( v14 == NULL )
			return;
		v14->CopyFromOtherItem(v17);

		if( this->CPCItemInventoryMgr::Add(v14, 0, 0, 1, 0) )
		{
			g_itemLog->CItemLog::AddItemLog(4, m_owner, other, v14, cost, v14->m_count, NULL);

			m_owner->CPC::DeleteMoney(cost);
			other->CPC::AddMoney(cost);
			other->m_pcitemInventoryMgr.CPCItemInventoryMgr::FreeInventoryItem(v17);
			other->m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifySoldedResultOnMCStore(index, count);
			other->m_pcitemInventoryMgr.CPCItemInventoryMgr::RefreshItemWeight();
		}
		else
		{
			other->m_pcitemInventoryMgr.m_mcStoreItem.Add(v17, price, 0);
			this->CPCItemInventoryMgr::FreeInventoryItem(v14);

		}
	}

	if( sumOfTotal >= g_MaxZenyStoreLog )
		g_itemLog->CItemLog::AddItemLog(4, m_owner, other, NULL, sumOfTotal, 0, NULL);
}


hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_IsMCStoreOpen(SERVER, "CPCItemInventoryMgr::IsMCStoreOpen");
int CPCItemInventoryMgr::IsMCStoreOpen(void)
{
	return (this->*_IsMCStoreOpen)();

	return m_mcStoreItem.m_isMCStoreOpen;
}


hook_method<void (CPCItemInventoryMgr::*)(float overcharge)> CPCItemInventoryMgr::_NotifyMySellableItem(SERVER, "CPCItemInventoryMgr::NotifyMySellableItem");
void CPCItemInventoryMgr::NotifyMySellableItem(float overcharge)
{
	return (this->*_NotifyMySellableItem)(overcharge);

	char outbuf[1024];
	int outlen = 0;

	for( mystd::vector<IVItItem*>::iterator it = m_bodyItem.CPCItemInventory::GetDataBeginIterator(); it != m_bodyItem.CPCItemInventory::GetDataEndIterator() && outlen <= 1000; ++it )
	{
		IVItItem* item = *it;

		CITP* itp = g_itpMgr->CITPMgr::GetITP(item->m_ID);
		if( itp == NULL )
			continue;

		if( itp->GetType() == TYPE_QUEST )
			continue;

		if( item->IVItItem::IsMovable() & 0x10 )
			continue;

		SELL_ITEM selItem;
		selItem.index = item->m_index;
		selItem.price = (int)(itp->m_price * 0.5);
		selItem.overchargeprice = (int)(itp->m_price * overcharge * 0.5);

		memcpy(&outbuf[outlen], &selItem, sizeof(SELL_ITEM));
		outlen += sizeof(SELL_ITEM);
	}

	PACKET_ZC_PC_SELL_ITEMLIST outpacket;
	outpacket.PacketType = HEADER_ZC_PC_SELL_ITEMLIST;
	outpacket.PacketLength = sizeof(outpacket) + outlen;
	m_owner->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	m_owner->CPC::Send(outlen, outbuf);
}


hook_method<void (CPCItemInventoryMgr::*)(int par1)> CPCItemInventoryMgr::_OnExchangeItem(SERVER, "CPCItemInventoryMgr::OnExchangeItem");
void CPCItemInventoryMgr::OnExchangeItem(int par1)
{
	return (this->*_OnExchangeItem)(par1);

	//TODO
}


hook_method<IVItItem* (CPCItemInventoryMgr::*)(unsigned short ID, short count)> CPCItemInventoryMgr::_AllocInventoryItem(SERVER, "CPCItemInventoryMgr::AllocInventoryItem");
IVItItem* CPCItemInventoryMgr::AllocInventoryItem(unsigned short ID, short count)
{
	return (this->*_AllocInventoryItem)(ID, count);

	return (m_IVItItemFactory.*(((CIVItItemFactory::vtable_t*)m_IVItItemFactory.vtable)->AllocInventoryItem))(ID, count);
}


hook_method<void (CPCItemInventoryMgr::*)(InventoryItem* item)> CPCItemInventoryMgr::_FreeInventoryItem(SERVER, "CPCItemInventoryMgr::FreeInventoryItem");
void CPCItemInventoryMgr::FreeInventoryItem(InventoryItem* item)
{
	return (this->*_FreeInventoryItem)(item);

	m_IVItItemFactory.CIVItItemFactory::FreeInventoryItem(item);
}


hook_method<void (CPCItemInventoryMgr::*)(unsigned long type, IVItItem* item)> CPCItemInventoryMgr::_NotifyAckAddItemToBody(SERVER, "CPCItemInventoryMgr::NotifyAckAddItemToBody");
void CPCItemInventoryMgr::NotifyAckAddItemToBody(unsigned long type, IVItItem* item)
{
	return (this->*_NotifyAckAddItemToBody)(type, item);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(unsigned short ITID)> CPCItemInventoryMgr::_InsertEmpeliumItem(SERVER, "CPCItemInventoryMgr::InsertEmpeliumItem");
void CPCItemInventoryMgr::InsertEmpeliumItem(unsigned short ITID)
{
	return (this->*_InsertEmpeliumItem)(ITID);

	//TODO
}


hook_method<IVItItem* (CPCItemInventoryMgr::*)(int dbkey)> CPCItemInventoryMgr::_SearchPet(SERVER, "CPCItemInventoryMgr::SearchPet");
IVItItem* CPCItemInventoryMgr::SearchPet(int dbkey)
{
	return (this->*_SearchPet)(dbkey);

	//TODO
}


//hook_method<CPC* (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_GetPC(SERVER, "CPCItemInventoryMgr::GetPC");
CPC* CPCItemInventoryMgr::GetPC(void)
{
//	return (this->*_GetPC)();

	return m_owner;
}


hook_method<void (CPCItemInventoryMgr::*)(CItem* item)> CPCItemInventoryMgr::_RandomDivision(SERVER, "CPCItemInventoryMgr::RandomDivision");
void CPCItemInventoryMgr::RandomDivision(CItem* item)
{
	return (this->*_RandomDivision)(item);

	unsigned short ITID = item->CItem::GetITID();

	if( !g_itpMgr->CITPMgr::GetITP(ITID) )
		return;

	int nMembers = m_owner->m_groupMember.size();

	int v6 = g_itpMgr->CITPMgr::GetItemWeight(ITID) * item->m_itemInfo.count;

	CPC* v5;
	mystd::list<unsigned long>::iterator it;
	for( it = m_owner->m_groupMember.begin(); it != m_owner->m_groupMember.end(); ++it )
	{
		if( GetServerRandom(0, 20000) % nMembers == 0 )
		{
			v5 = (CPC*) g_characterMgr->CCharacterMgr::FindCharacter((*it), PC_TYPE);
			if( v5 )
			{
				if( v5->IsMyArea(item, 5) )
				{
					int refininglevel = v6 + v5->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemWeight();
					int v9 = v5->CPC::GetBodyMaxItemWeight();
					if ( v9 > refininglevel )
						break;
				}
			}
		}
	}

	if( it == m_owner->m_groupMember.end() )
		v5 = this->m_owner;

	IVItItem* ivit = v5->m_pcitemInventoryMgr.AllocInventoryItem(item->CItem::GetITID(), item->m_itemInfo.count);
	if( !ivit )
		return;

	int identifyflag;
	int slot1;
	int slot2;
	int slot3;
	int slot4;
	item->GetParameterValue(VAR_ISIDENTIFIED, identifyflag);
	ivit->m_isIdentified = ( identifyflag != 0 );
	ivit->IVItItem::SetUniqueIdentityNumV2(item->m_itemInfo.unique_identity_numberV2);
	ivit->IVItItem::SetHireExpireDate(item->m_itemInfo.hire_expire_date);
	item->GetParameterValue(VAR_ITEM_SLOT1, slot1);
	item->GetParameterValue(VAR_ITEM_SLOT2, slot2);
	item->GetParameterValue(VAR_ITEM_SLOT3, slot3);
	item->GetParameterValue(VAR_ITEM_SLOT4, slot4);
	ivit->m_slotInfo.info[0] = slot1;
	ivit->m_slotInfo.info[1] = slot2;
	ivit->m_slotInfo.info[2] = slot3;
	ivit->m_slotInfo.info[3] = slot4;

	if( ivit->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
	{
		int isdamaged;
		int refininglevel;
		item->GetParameterValue(VAR_ISDAMAGED, isdamaged);
		item->GetParameterValue(VAR_REFININGLEVEL, refininglevel);
		((IVItEquipItem*)ivit)->m_isDamaged = ( isdamaged != 0 );
		((IVItEquipItem*)ivit)->m_refiningLevel = refininglevel;
	}

	if( !v5->m_pcitemInventoryMgr.CPCItemInventoryMgr::Add(ivit, 0, 0, 1, 0) )
	{
		v5->m_pcitemInventoryMgr.CPCItemInventoryMgr::FreeInventoryItem((InventoryItem *)ivit);
		return;
	}

	v5->m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifyPickUpToParty(ivit);
	g_itemLog->CItemLog::AddItemLog(1, v5, NULL, ivit, 0, ivit->m_count, NULL);
	v5->m_pcitemInventoryMgr.CPCItemInventoryMgr::RefreshItemWeight();

	// send item pickup animation
	PACKET_ZC_NOTIFY_ACT outpacket2;
	outpacket2.PacketType = HEADER_ZC_NOTIFY_ACT;
	outpacket2.startTime = timeGetTime();
	outpacket2.GID = m_owner->GetAccountID();
	outpacket2.targetGID = item->GetAccountID();
	outpacket2.action = 1;

	this->m_owner->CPC::Send(sizeof(outpacket2), (char *)&outpacket2);
	this->m_owner->CCharacter::MultiCast((char *)&outpacket2, sizeof(outpacket2));

	g_characterMgr->CCharacterMgr::RemoveCharacter(item);
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned long ITID)> CPCItemInventoryMgr::_GetCountItemOfMyGID(SERVER, "CPCItemInventoryMgr::GetCountItemOfMyGID");
int CPCItemInventoryMgr::GetCountItemOfMyGID(unsigned long ITID)
{
	return (this->*_GetCountItemOfMyGID)(ITID);

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(unsigned long ITID, int count)> CPCItemInventoryMgr::_RemoveItemOfMyGID(SERVER, "CPCItemInventoryMgr::RemoveItemOfMyGID");
int CPCItemInventoryMgr::RemoveItemOfMyGID(unsigned long ITID, int count)
{
	return (this->*_RemoveItemOfMyGID)(ITID, count);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(unsigned long ITID, int count, unsigned long sGID)> CPCItemInventoryMgr::_CreateItemOfMyGID(SERVER, "CPCItemInventoryMgr::CreateItemOfMyGID");
void CPCItemInventoryMgr::CreateItemOfMyGID(unsigned long ITID, int count, unsigned long sGID)
{
	return (this->*_CreateItemOfMyGID)(ITID, count, sGID);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(int bResetItem, int bResetMoney)> CPCItemInventoryMgr::_CancelMailItem(SERVER, "CPCItemInventoryMgr::CancelMailItem");
void CPCItemInventoryMgr::CancelMailItem(int bResetItem, int bResetMoney)
{
	return (this->*_CancelMailItem)(bResetItem, bResetMoney);

	//TODO
}


hook_method<int (CPCItemInventoryMgr::*)(IVItItem& Item, int& ItemCounter, char* ItemBuffer, int& BufferLen, unsigned long& Money)> CPCItemInventoryMgr::_GetMailItem(SERVER, "CPCItemInventoryMgr::GetMailItem");
int CPCItemInventoryMgr::GetMailItem(IVItItem& Item, int& ItemCounter, char* ItemBuffer, int& BufferLen, unsigned long& Money)
{
	return (this->*_GetMailItem)(Item, ItemCounter, ItemBuffer, BufferLen, Money);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_CancelAuctionItem(SERVER, "CPCItemInventoryMgr::CancelAuctionItem");
void CPCItemInventoryMgr::CancelAuctionItem(void)
{
	return (this->*_CancelAuctionItem)();

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(int npcAID, int ITID, int count)> CPCItemInventoryMgr::_SetItemPartyInMap(SERVER, "CPCItemInventoryMgr::SetItemPartyInMap");
void CPCItemInventoryMgr::SetItemPartyInMap(int npcAID, int ITID, int count)
{
	return (this->*_SetItemPartyInMap)(npcAID, ITID, count);

	//TODO
}


hook_method<void (CPCItemInventoryMgr::*)(short index, short count)> CPCItemInventoryMgr::_NotifySoldedResultOnMCStore(SERVER, "CPCItemInventoryMgr::NotifySoldedResultOnMCStore");
void CPCItemInventoryMgr::NotifySoldedResultOnMCStore(short index, short count)
{
	return (this->*_NotifySoldedResultOnMCStore)(index, count);

	//TODO
}
