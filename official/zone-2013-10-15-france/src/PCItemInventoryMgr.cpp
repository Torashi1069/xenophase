#include "CharacterMgr.h"
#include "Enum.h"
#include "ItemLog.h"
#include "ITPMgr.h"
#include "PC.h"
#include "PCCartItemIV.h"
#include "PCItemInventoryMgr.h"
#include "PCStoreItemIV.h"
#include "ZoneScript.h"
#include "Common/Packet.h"
#include "Player/Inventory/CIVItEquipItem.h"
#include "Player/Inventory/CIVItItem.h"
#include "Player/Inventory/CIVItNormalItem.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/VarLenPacketPtr.h"


CPCItemInventoryMgr::CPCItemInventoryMgr() // 155-156
{
}


CPCItemInventoryMgr::~CPCItemInventoryMgr() // 159-160
{
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__Init(EXEPATH(), "CPCItemInventoryMgr::Init");
void CPCItemInventoryMgr::Init() // 163-191
{
	void* hookptr = CPCItemInventoryMgr__Init;
	__asm mov edi, this
	__asm call hookptr
	return; //TODO
/*
	m_owner = NULL;
	m_bodyItemParsing = 0;
	m_MCStoreUniqueID = 0;
	m_bodyItem.CPCBodyItemIV::Init();
	m_bodyItem.CPCBodyItemIV::SetOwner(this);
	m_cartItem.CPCCartItemIV::Init();
	m_cartItem.CPCCartItemIV::SetOwner(this);
	m_storeItem.CPCStoreItemIV::Init();
	m_storeItem.CPCStoreItemIV::SetOwner(this);
	m_exchangeItem.CPCExchangeItemIV::Init();
	m_exchangeItem.CPCExchangeItemIV::SetOwner(this);
	m_equipedItem.CPCEquipedItemIV::Init();
	m_equipedItem.CPCEquipedItemIV::SetOwner(this);
	m_mcStoreItem.CPCMCStoreItemIV::Init();
	m_mcStoreItem.CPCMCStoreItemIV::SetOwner(this);
	m_BuyingStore.CPCBuyingStore::Init();
	m_MailItem.CPCExtraItemIV::Init();
	m_MailItem.CPCExtraItemIV::SetOwner(this);
	m_AuctionItem.CPCExtraItemIV::Init();
	m_AuctionItem.CPCExtraItemIV::SetOwner(this);
	m_IVItItemFactory.CIVItItemFactory::Reset();
	m_tempItemInventory.clear();
*/
}


CPC* CPCItemInventoryMgr::GetPC() // (267.h)
{
	return m_owner;
}


void CPCItemInventoryMgr::SetMyOwner(CPC* owner) // 217-219
{
	m_owner = owner;
}


void CPCItemInventoryMgr::StoreItemReset() // (85.h)
{
	m_storeItem.Reset();
}


hook_func<IVItItem* (CPCItemInventoryMgr::*)(IVItItem* item, unsigned long type, unsigned short desPos, BOOL IsClientNotified, BOOL IsFroceInsert)> CPCItemInventoryMgr__Add(EXEPATH(), "CPCItemInventoryMgr::Add");
IVItItem* CPCItemInventoryMgr::Add(IVItItem* item, unsigned long type, unsigned short desPos, BOOL IsClientNotified, BOOL IsFroceInsert) // 233-576
{
	return (this->*CPCItemInventoryMgr__Add)(item, type, desPos, IsClientNotified, IsFroceInsert); //TODO
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__isBodyAddMailItem(EXEPATH(), "CPCItemInventoryMgr::isBodyAddMailItem");
BOOL CPCItemInventoryMgr::isBodyAddMailItem(unsigned short ITID, unsigned long ItemType, int count, EQUIPSLOTINFO slotInfo, __int64 UniqueSerialNum) // 581-632
{
	BOOL result;
	void* hookptr = CPCItemInventoryMgr__isBodyAddMailItem;
	__asm push dword ptr slotInfo + 4
	__asm push dword ptr slotInfo + 0
	__asm push dword ptr UniqueSerialNum + 4
	__asm push dword ptr UniqueSerialNum + 0
	__asm mov eax, ItemType
	__asm push ITID
	__asm mov ecx, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	if( ItemType != INVENTORYITEMTYPE_ITEM
	 && ItemType != INVENTORYITEMTYPE_NORMALITEM
	 && ItemType != INVENTORYITEMTYPE_NORMALARROWITEM
	 && ItemType != INVENTORYITEMTYPE_EQUIPITEM
	 && ItemType != INVENTORYITEMTYPE_CASHPOINTITEM )
		return FALSE;

	if( m_owner->CPC::GetBodyMaxItemWeight() < this->CPCItemInventoryMgr::GetBodyItemWeight() + count * g_itpMgr.CITPMgr::GetItemWeight(ITID) )
		return FALSE;

	int GID = (slotInfo.info[2] << 0) | (slotInfo.info[3] << 16);

	if( m_exchangeItem.GetSize() + m_equipedItem.GetSize() + m_bodyItem.GetSize() >= 100 )
	{
		IVItItem* item = m_bodyItem.CPCItemInventory::SearchItem(ITID, GID, UniqueSerialNum);
		if( item != NULL )
		{
			unsigned long type = item->GetType();
			if( type == INVENTORYITEMTYPE_NORMALITEM || type == INVENTORYITEMTYPE_NORMALARROWITEM )
			{
				if( (unsigned int)(count + item->IVItItem::GetCount()) > 30000 )
					return FALSE;

				return TRUE;
			}
		}

		return FALSE;
	}
	else
	{
		IVItItem* item = m_bodyItem.CPCItemInventory::SearchItem(ITID, GID, UniqueSerialNum);
		if( item != NULL )
		{
			if( (unsigned int)(count + item->IVItItem::GetCount()) > 30000 )
				return FALSE;
		}

		return TRUE;
	}
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetEquipLocationbyIndex(EXEPATH(), "CPCItemInventoryMgr::GetEquipLocationbyIndex");
unsigned long CPCItemInventoryMgr::GetEquipLocationbyIndex(const int in_index) // 660-667
{
	unsigned long result;
	void* hookptr = CPCItemInventoryMgr__GetEquipLocationbyIndex;
	__asm push in_index
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetEquipItemIDbyIndex(EXEPATH(), "CPCItemInventoryMgr::GetEquipItemIDbyIndex");
unsigned short CPCItemInventoryMgr::GetEquipItemIDbyIndex(const int in_index) // 670-677
{
	unsigned short result;
	void* hookptr = CPCItemInventoryMgr__GetEquipItemIDbyIndex;
	__asm push in_index
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__SearchItem(EXEPATH(), "CPCItemInventoryMgr::SearchItem");
IVItItem* CPCItemInventoryMgr::SearchItem(unsigned long type, short index) // 680-702
{
	IVItItem* result;
	void* hookptr = CPCItemInventoryMgr__SearchItem;
	__asm push index
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	switch( type )
	{
	case BODY:
		return m_bodyItem.CPCItemInventory::SearchItemByIndex(index);
	case CART:
		return m_cartItem.CPCItemInventory::SearchItemByIndex(index);
	case STORE:
		return m_storeItem.CPCItemInventory::SearchItemByIndex(index);
	case EXCHANGE:
		return m_exchangeItem.CPCItemInventory::SearchItemByIndex(index);
	case EQUIPMENT:
		return m_equipedItem.CPCItemInventory::SearchItemByIndex(index);
	case MCSTORE:
		return m_mcStoreItem.CPCItemInventory::SearchItemByIndex(index);
	case MAIL:
		return m_MailItem.CPCItemInventory::SearchItemByIndex(index);
	case AUCTION:
		return m_AuctionItem.CPCItemInventory::SearchItemByIndex(index);
//	case GUILDSTORAGE:
	default:
		return NULL;
	};
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__SearchItemByID(EXEPATH(), "CPCItemInventoryMgr::SearchItemByID");
IVItItem* CPCItemInventoryMgr::SearchItemByID(unsigned long type, unsigned short ITID) // 733-755
{
	IVItItem* result;
	unsigned long type_ = type;
	void* hookptr = CPCItemInventoryMgr__SearchItemByID;
	__asm mov cx, ITID
	__asm mov edx, type_
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	switch( type )
	{
	case BODY:
		return m_bodyItem.CPCItemInventory::SearchItemByID(ITID, false);
	case CART:
		return m_cartItem.CPCItemInventory::SearchItemByID(ITID, false);
	case STORE:
		return m_storeItem.CPCItemInventory::SearchItemByID(ITID, false);
	case EXCHANGE:
		return m_exchangeItem.CPCItemInventory::SearchItemByID(ITID, false);
	case EQUIPMENT:
		return m_equipedItem.CPCItemInventory::SearchItemByID(ITID, false);
	case MCSTORE:
	case MAIL:
	case AUCTION:
		return m_mcStoreItem.CPCItemInventory::SearchItemByID(ITID, false);
//	case GUILDSTORAGE:
	default:
		return NULL;
	}
*/
}


void CPCItemInventoryMgr::ParseDBFmtStoreItemData(const int in_Length, const unsigned char* in_pData) // 1732-1786
{
	if( this->CPCItemInventoryMgr::IsStoreOpen() )
		return;
	
	if( in_Length == -1 )
		return;

	m_storeItem.Reset();
	m_storeItem.CPCStoreItemIV::SetStoreOpenFlag(true);

	if( in_Length != 0 && in_Length != 2 )
	{
		if( !m_owner->m_pcItem.CPCItem::ParseStoredItem((const char*)in_pData, in_Length) )
		{
			Request request;
			request.Request::SetID(RT_STOREITEM_PARSING);
			request.par1 = (int)in_pData;
			request.par2 = in_Length;

			if( this->CPCItemInventoryMgr::Parse(&request, false, false, false) != PASERRET::ERROR_NONE )
			{
				m_storeItem.CPCStoreItemIV::SetStoreOpenFlag(false);
				m_owner->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
				return;
			}
		}

		this->CPCItemInventoryMgr::NotifyItemInfo(STORE);
	}
	else
	{
		PACKET_ZC_STORE_NORMAL_ITEMLIST outpacket1;
		outpacket1.PacketType = HEADER_ZC_STORE_NORMAL_ITEMLIST;
		outpacket1.Length = sizeof(outpacket1) + 0;
		m_owner->Send(sizeof(outpacket1), (const char*)&outpacket1);
	}

	this->CPCItemInventoryMgr::NotifyStoreItemCountInfo();
}


void CPCItemInventoryMgr::NotifyStoreItemCountInfo() // 1814-1821
{
	PACKET_ZC_NOTIFY_STOREITEM_COUNTINFO outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_STOREITEM_COUNTINFO;
	outpacket.curCount = m_storeItem.GetSize();
	outpacket.maxCount = m_owner->CPC::GetStoreMaxItemSize();
	m_owner->Send(sizeof(outpacket), (const char*)&outpacket);
}


hook_func<void (CPCItemInventoryMgr::*)(unsigned long loc)> CPCItemInventoryMgr__TakeOffEquip(EXEPATH(), "CPCItemInventoryMgr::TakeOffEquip");
void CPCItemInventoryMgr::TakeOffEquip(unsigned long loc) // 2421-2469
{
	return (this->*CPCItemInventoryMgr__TakeOffEquip)(loc); //TODO
/*
	switch( loc )
	{
	case LOCATION_HEAD_TMB:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD2);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD3);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD_TMB);
	break;
	case LOCATION_HEAD_MB:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD3);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD_MB);
	break;
	case LOCATION_HEAD_TM:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD2);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD3);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD_TM);
	break;
	case LOCATION_HEAD_TB:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD2);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_HEAD);
	break;
	case LOCATION_COSTUME_HEAD_TMB:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD2);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD3);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD);
	break;
	case LOCATION_COSTUME_HEAD_MB:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD3);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD);
	break;
	case LOCATION_COSTUME_HEAD_TM:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD2);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD3);
	break;
	case LOCATION_COSTUME_HEAD_TB:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD2);
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(LOCATION_COSTUME_HEAD);
	break;
	default:
		m_equipedItem.CPCEquipedItemIV::TakeOffEquipItem(loc);
	break;
	};
*/
}


hook_func<int (CPCItemInventoryMgr::*)()> CPCItemInventoryMgr__GetBodyItemWeight(EXEPATH(), "CPCItemInventoryMgr::GetBodyItemWeight");
int CPCItemInventoryMgr::GetBodyItemWeight() // 4736-4738
{
	return (this->*CPCItemInventoryMgr__GetBodyItemWeight)(); //TODO
/*
	return m_bodyItem.m_weight + m_exchangeItem.m_weight + m_equipedItem.m_weight;
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetCountItemOfMyGID(EXEPATH(), "CPCItemInventoryMgr::GetCountItemOfMyGID");
int CPCItemInventoryMgr::GetCountItemOfMyGID(unsigned long ITID) // 5300-5332
{
	int result;
	void* hookptr = CPCItemInventoryMgr__GetCountItemOfMyGID;
	__asm push ITID
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	CITP* itp = g_itpMgr.CITPMgr::GetITP(ITID);
	if( itp == NULL )
		return 0;

	if( !itp->IsApparel() )
	{
		IVItItem* item = m_bodyItem.CPCItemInventory::SearchItemByID_GID(ITID, m_owner->CPC::GetCharacterID());
		if( item == NULL )
			return 0;

		return item->IVItItem::GetCount();
	}
	else
	{
		int count = 0;
		unsigned long myGID = m_owner->CPC::GetCharacterID();

		for( std::vector<IVItItem*>::iterator iter = m_bodyItem.m_itemData.begin(); iter != m_bodyItem.m_itemData.end(); ++iter )
		{
			IVItItem* item = *iter;
			if( item->InventoryItem::GetID() != ITID )
				continue;

			unsigned short itemVersion = item->m_slotInfo.info[0];
			if( itemVersion != NAMED_ITEM_VERSION && itemVersion != BLACKSMITH_ITEM_VERSION )
				continue;

			unsigned long itemGID = (item->m_slotInfo.info[2] << 0) | (item->m_slotInfo.info[3] << 16);
			if( itemGID != myGID )
				continue;

			++count;
		}

		return count;
	}
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetBodyItemCount(EXEPATH(), "CPCItemInventoryMgr::GetBodyItemCount");
BOOL CPCItemInventoryMgr::GetBodyItemCount(unsigned short id, int& value) // 5422-5437
{
	BOOL result;
	void* hookptr = CPCItemInventoryMgr__GetBodyItemCount;
	__asm lea edi, value
	__asm push id
	__asm mov esi, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	IVItItem* item = m_bodyItem.CPCItemInventory::SearchItemByID(id, false);
	value = 0;

	if( item == NULL )
		item = m_equipedItem.CPCItemInventory::SearchItemByID(id, false);
	
	if( item == NULL )
		return FALSE;

	value = item->IVItItem::GetCount();
	return TRUE;
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetJustBodyItemCount(EXEPATH(), "CPCItemInventoryMgr::GetJustBodyItemCount");
BOOL CPCItemInventoryMgr::GetJustBodyItemCount(unsigned short id, int& value) // 5440-5450
{
	BOOL result;
	void* hookptr = CPCItemInventoryMgr__GetJustBodyItemCount;
	__asm lea esi, value
	__asm push id
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	IVItItem* item = m_bodyItem.CPCItemInventory::SearchItemByID(id, false);
	value = 0;

	if( item == NULL )
		return FALSE;

	value = item->IVItItem::GetCount();
	return TRUE;
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetJustEquipItemCount(EXEPATH(), "CPCItemInventoryMgr::GetJustEquipItemCount");
BOOL CPCItemInventoryMgr::GetJustEquipItemCount(unsigned short id, int& value) // 5453-5463
{
	BOOL result;
	void* hookptr = CPCItemInventoryMgr__GetJustEquipItemCount;
	__asm lea esi, value
	__asm push id
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	IVItItem* item = m_equipedItem.CPCItemInventory::SearchItemByID(id, false);
	value = 0;

	if( item == NULL )
		return FALSE;

	value = item->IVItItem::GetCount();
	return TRUE;
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__OnSetBodyItem(EXEPATH(), "CPCItemInventoryMgr::OnSetBodyItem");
void CPCItemInventoryMgr::OnSetBodyItem(int npcAID, int ITID, int count) // 5466-5554
{
	void* hookptr = CPCItemInventoryMgr__OnSetBodyItem;
	__asm mov ecx, count
	__asm push ITID
	__asm push this
	__asm call hookptr
	return; //TODO
/*
	if( count < 0 )
		return;

	IVItItem* bodyItem = m_bodyItem.CPCItemInventory::SearchItemByID(ITID, false);
	if( bodyItem == NULL )
	{
		IVItItem aitem;
		aitem.InventoryItem::SetID(ITID);
		aitem.IVItItem::SetCount(count);

		IVItItem* newItem = this->CPCItemInventoryMgr::Add(&aitem, BODY, 0, TRUE, FALSE);
		if( newItem != NULL )
			g_itemLog.CItemLog::AddItemLog(ITEMLOG_NPC_SETITEM, m_owner, NULL, newItem, 0, count, NULL, 0);
	}
	else
	if( bodyItem->IVItItem::GetCount() <= count )
	{
		IVItItem aitem;
		aitem.InventoryItem::SetID(ITID);
		aitem.IVItItem::SetCount(count - bodyItem->IVItItem::GetCount());

		IVItItem* newItem = this->CPCItemInventoryMgr::Add(&aitem, BODY, 0, TRUE, FALSE);
		if( newItem != NULL )
			g_itemLog.CItemLog::AddItemLog(ITEMLOG_NPC_SETITEM, m_owner, NULL, newItem, 0, count - bodyItem->IVItItem::GetCount(), NULL, 0);
	}
	else
	{
		m_bodyItem.Delete(bodyItem->IVItItem::GetIndex(), bodyItem->IVItItem::GetCount() - count);
		g_itemLog.CItemLog::AddItemLog(ITEMLOG_NPC_SETITEM, m_owner, NULL, bodyItem, 0, bodyItem->IVItItem::GetCount() - count, NULL, 0);
	}
*/
}


void CPCItemInventoryMgr::OnMediatorRequest(Request* request) // 4642-4668
{
	if( request == NULL || m_owner == NULL )
		return;

	switch( request->Request::GetID() )
	{
	case RT_REQ_PCVAR:
	{
		unsigned short id = static_cast<unsigned short>(request->par1);
		int value = static_cast<int>(request->par2);
		m_owner->GetParameterValue(id, value);
	}
	break;
	case RT_NOTIFY_VARCHANGE:
	{
		unsigned long varID = static_cast<unsigned long>(request->par1);
		int par1 = static_cast<int>(request->par2);
		m_owner->CPC::NotifyParameter(varID, par1);
	}
	break;
	case RT_NOTIFY_ARROWEQUIPED:
	{
		unsigned short index = static_cast<unsigned short>(request->par1);
		m_owner->CPC::NotifyArrowEquiped(index);
	}
	break;
	case RT_SEND_PACKET:
	{
		int len = static_cast<int>(request->par1);
		const char* buf = reinterpret_cast<const char*>(request->par2);
		m_owner->Send(len, buf);
	}
	break;
	case RT_UPDATE_PARAMETER:
	{
		unsigned short id = static_cast<unsigned short>(request->par1);
		int value = static_cast<int>(request->par2);
		m_owner->UpdateParameterValue(id, value);
	}
	break;
	case RT_NOTIFY_ATTACKRANGE:
	{
		m_owner->CPC::NotifyAttackRange();
	}
	break;
	};
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetBodyItemWeightByPercent(EXEPATH(), "CPCItemInventoryMgr::GetBodyItemWeightByPercent");
int CPCItemInventoryMgr::GetBodyItemWeightByPercent() // 7044-7046
{
	int result;
	void* hookptr = CPCItemInventoryMgr__GetBodyItemWeightByPercent;
	__asm mov edi, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	return 100 * this->CPCItemInventoryMgr::GetBodyItemWeight() / max(m_owner->CPC::GetBodyMaxItemWeight(), 1);
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetITPEquipedWeapon(EXEPATH(), "CPCItemInventoryMgr::GetITPEquipedWeapon");
CITP* CPCItemInventoryMgr::GetITPEquipedWeapon() // 7049-7050
{
	CITP* result;
	void* hookptr = CPCItemInventoryMgr__GetITPEquipedWeapon;
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	return m_equipedItem.CPCEquipedItemIV::GetITPEquipedWeapon();
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetEquipedWeaponType(EXEPATH(), "CPCItemInventoryMgr::GetEquipedWeaponType");
short CPCItemInventoryMgr::GetEquipedWeaponType() // 7054-7057
{
	short result;
	void* hookptr = CPCItemInventoryMgr__GetEquipedWeaponType;
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
/*
	CITP* itp = m_equipedItem.CPCEquipedItemIV::GetITPEquipedWeapon();
	if( itp == NULL )
		return WEAPONTYPE_NONE;

	return itp->GetClass();
*/
}


int CPCItemInventoryMgr::IsStoreOpen() // 7067-7068
{
	return m_storeItem.CPCStoreItemIV::IsOpen();
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetPlusPowerOfItem(EXEPATH(), "CPCItemInventoryMgr::GetPlusPowerOfItem");
int CPCItemInventoryMgr::GetPlusPowerOfItem(unsigned long type) // 7072-7074
{
	int result;
	void* hookptr = CPCItemInventoryMgr__GetPlusPowerOfItem;
	unsigned long type_ = type;
	__asm push type_
	__asm mov ecx, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	return m_equipedItem.CPCEquipedItemIV::GetPlusPowerOfItem(type);
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__DeleteItem(EXEPATH(), "CPCItemInventoryMgr::DeleteItem");
BOOL CPCItemInventoryMgr::DeleteItem(unsigned long type, short index, short count) // 7249-7267
{
	BOOL result;
	void* hookptr = CPCItemInventoryMgr__DeleteItem;
	unsigned long type_ = type;
	__asm mov dx, count
	__asm mov si, index
	__asm mov ecx, type_
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	switch( type )
	{
	case BODY:
		return m_bodyItem.Delete(index, count);
	case CART:
		return m_cartItem.Delete(index, count);
	case STORE:
		return m_storeItem.Delete(index, count);
	case EXCHANGE:
		return m_exchangeItem.Delete(index, count);
	case EQUIPMENT:
		return m_equipedItem.Delete(index, count);
	case MCSTORE:
		return m_mcStoreItem.Delete(index, count);
	default:
		return FALSE;
	};
*/
}


int CPCItemInventoryMgr::GetAttackDistance() // 7275-7283
{
	CITP* itp = this->CPCItemInventoryMgr::GetITPEquipedWeapon();
	if( itp != NULL )
		return itp->GetAttRange();
	else
		return 1;
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetEquipedArrow(EXEPATH(), "CPCItemInventoryMgr::GetEquipedArrow");
IVItItem* CPCItemInventoryMgr::GetEquipedArrow() // 7286-7287
{
	IVItItem* result;
	void* hookptr = CPCItemInventoryMgr__GetEquipedArrow;
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	return m_equipedItem.CPCEquipedItemIV::GetEquipedArrow();
*/
}


void CPCItemInventoryMgr::RefreshItemWeight() // 7415-7430
{
	int percent = this->CPCItemInventoryMgr::GetBodyItemWeightByPercent();
	if( percent >= 90 )
	{
		m_owner->SetEffective(EFST_WEIGHTOVER90, 9999, 1, 0, 0, 0);
		m_owner->ResetEffective(EFST_WEIGHTOVER50, 0);
	}
	else
	if( percent >= 50 )
	{
		m_owner->SetEffective(EFST_WEIGHTOVER50, 9999, 1, 0, 0, 0);
		m_owner->ResetEffective(EFST_WEIGHTOVER90, 0);
	}
	else
	{
		if( m_owner->GetEffective(EFST_WEIGHTOVER50, 0) )
			m_owner->ResetEffective(EFST_WEIGHTOVER50, 0);

		if( m_owner->GetEffective(EFST_WEIGHTOVER90, 0) )
			m_owner->ResetEffective(EFST_WEIGHTOVER90, 0);
	}

	m_owner->CPC::NotifyParameter(VAR_WEIGHT, 0);
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__AllocInventoryItem(EXEPATH(), "CPCItemInventoryMgr::AllocInventoryItem");
IVItItem* CPCItemInventoryMgr::AllocInventoryItem(unsigned short ID, short count) // 7433-7435
{
	IVItItem* result;
	void* hookptr = CPCItemInventoryMgr__AllocInventoryItem;
	__asm push count
	__asm push ID
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	return m_IVItItemFactory.AllocInventoryItem(ID, count);
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__FreeInventoryItem(EXEPATH(), "CPCItemInventoryMgr::FreeInventoryItem");
void CPCItemInventoryMgr::FreeInventoryItem(InventoryItem* item) // 7438-7440
{
	void* hookptr = CPCItemInventoryMgr__FreeInventoryItem;
	__asm mov edi, item
	__asm mov eax, this
	__asm call hookptr
	return; //TODO
/*
	m_IVItItemFactory.CIVItItemFactory::FreeInventoryItem(item);
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__GetEquipedItem(EXEPATH(), "CPCItemInventoryMgr::GetEquipedItem");
IVItEquipItem* CPCItemInventoryMgr::GetEquipedItem(unsigned long loc) // 7785-7786
{
	IVItEquipItem* result;
	void* hookptr = CPCItemInventoryMgr__GetEquipedItem;
	__asm mov edx, loc
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	return m_equipedItem.CPCEquipedItemIV::GetEquipedItem(loc);
*/
}


void CPCItemInventoryMgr::ReqMakeArrow(unsigned short id) // 8031-8155
{
	if( id == -1 )
		return;

	if( m_owner->CPC::GetCategoryFirstJob() == JT_NOVICE )
	{
		m_owner->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	switch( m_owner->CPC::GetCategoryFirstJob() )
	{
	case JT_MAGICIAN:
	{
		std::map<unsigned short,std::vector<extraITMInfo>> info = g_zoneScript.CZoneScript::GetMakingElementalInfo();
		std::map<unsigned short,std::vector<extraITMInfo>>::iterator it = info.find(id);
		if( it == info.end() )
			break;

		unsigned short ITID = it->first;
		std::vector<extraITMInfo> list = it->second;

		std::vector<extraITMInfo>::iterator i;
		for( i = list.begin(); i != list.end(); ++i )
			if( !m_owner->CPC::ConsumeItem(i->id, i->num, NULL, PACKET_ZC_DELETE_ITEM_FROM_BODY::DELETE_TYPE_NORMAL) )
				break;
		if( i != list.end() )
			break;

		m_owner->CPC::OnAddItem(ITID, 0, 1, 0, 0, 0);
	}
	break;
	case JT_ARCHER:
	{
		if( !m_owner->m_pcSkill.CPCSkill::GetSkill(SKID_AC_MAKINGARROW, FALSE) )
		{
			m_owner->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return;
		}

		std::map<unsigned short,std::vector<extraITMInfo>> info = g_zoneScript.CZoneScript::GetMakingArrowItemInfo();
		std::map<unsigned short,std::vector<extraITMInfo>>::iterator it = info.find(id);
		if( it == info.end() )
			break;

		if( !m_owner->CPC::ConsumeItem(it->first, 1, NULL, PACKET_ZC_DELETE_ITEM_FROM_BODY::DELETE_TYPE_NORMAL) )
			break;

		std::vector<extraITMInfo>::iterator i;
		for( i = it->second.begin(); i != it->second.end(); ++i )
			m_owner->CPC::OnAddItem(i->id, 0, i->num, 0, 0, 0);
	}
	break;
	default:
	{
		m_owner->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
	}
	break;
	};

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_owner, CM_ENABLEITEMMOVE, 0, 0, 0, 0);
}


BOOL CPCItemInventoryMgr::PutMailBinaryItem(char* ItemBuffer, int ItemLen) // 9176-9207
{
	Request request;
	request.Request::SetID(RT_BODYITEM_PARSING);
	request.par1 = (int)ItemBuffer;
	request.par2 = ItemLen;

	PASERRET::enumError ret = this->CPCItemInventoryMgr::Parse(&request, true, false, true);
	if( ret != PASERRET::ERROR_NONE )
	{
		if( ret != PASERRET::ERROR_ADD )
			m_owner->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());

		return FALSE;
	}

	this->CPCItemInventoryMgr::RefreshItemWeight();
	return TRUE;
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__Parse(EXEPATH(), "CPCItemInventoryMgr::Parse");
PASERRET::enumError CPCItemInventoryMgr::Parse(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType) // 10340-10354
{
	PASERRET::enumError result;
	void* hookptr = CPCItemInventoryMgr__Parse;
	__asm movzx eax, in_bUseItemType
	__asm push eax
	__asm movzx eax, in_bNotify
	__asm push eax
	__asm mov ecx, in_pRequest
	__asm mov ebx, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	return this->CPCItemInventoryMgr::ParseV4(in_pRequest, in_bNotify, in_bUseZip, in_bUseItemType);
*/
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__SearchItemByUniqueIdentityNum(EXEPATH(), "CPCItemInventoryMgr::SearchItemByUniqueIdentityNum");
IVItItem* CPCItemInventoryMgr::SearchItemByUniqueIdentityNum(const enumInventoryType in_InventoryType, const __int64 in_UID) // 10359-10372
{
	IVItItem* result;
	void* hookptr = CPCItemInventoryMgr__SearchItemByUniqueIdentityNum;
	__asm push dword ptr in_UID + 4
	__asm push dword ptr in_UID + 0
	__asm mov ecx, in_InventoryType
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	switch( in_InventoryType )
	{
	case BODY:      return m_bodyItem.CPCItemInventory::SearchItemByUniqueIdentityNum(in_UID);
	case CART:      return m_cartItem.CPCItemInventory::SearchItemByUniqueIdentityNum(in_UID);
	case STORE:     return m_storeItem.CPCItemInventory::SearchItemByUniqueIdentityNum(in_UID);
	case EXCHANGE:  return m_exchangeItem.CPCItemInventory::SearchItemByUniqueIdentityNum(in_UID);
	case EQUIPMENT: return m_equipedItem.CPCItemInventory::SearchItemByUniqueIdentityNum(in_UID);
	case MCSTORE:   return m_mcStoreItem.CPCItemInventory::SearchItemByUniqueIdentityNum(in_UID);
	case MAIL:      return m_MailItem.CPCItemInventory::SearchItemByUniqueIdentityNum(in_UID);
	case AUCTION:   return m_AuctionItem.CPCItemInventory::SearchItemByUniqueIdentityNum(in_UID);
	default:        return NULL;
	};
*/
}


void CPCItemInventoryMgr::HireItemCheckAdd(const enumInventoryType in_InventoryType, IVItItem* in_pItem) // 10375-10377
{
	m_owner->CPC::HireItemCheckAdd(in_InventoryType, in_pItem);
}


int CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_NORMALITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer) // 10467-10515
{
	if( in_Version > 0 )
	{
		if( in_Version == 1 || in_Version == 2 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "item DBValueParser: invalid versioninfo");
			return FALSE;
		}
		else
		if( in_Version == 3 )
		{
			IVItNormalItemData TempNormalItemData;
			memcpy_s(&TempNormalItemData, sizeof(TempNormalItemData), in_pIBDBuffer, sizeof(IVItNormalItemData));
			out_pItemINFO->ITID = TempNormalItemData.ITID;
			out_pItemINFO->count = TempNormalItemData.count;
			out_pItemINFO->IsIdentified = TempNormalItemData.IsIdentified;
			out_pItemINFO->slot = TempNormalItemData.slot;
			out_pItemINFO->UniqueSerialNum = 0;
			out_pItemINFO->HireExpireDate = 0;
		}
		else
		if( in_Version == 4 || in_Version == 5 )
		{
			IVItNormalItem NormalItem;
			NormalItem.IVItNormalItem::IBData_Set(in_pIBDBuffer);
			out_pItemINFO->ITID = NormalItem.InventoryItem::GetID();
			out_pItemINFO->count = NormalItem.IVItItem::GetCount();
			out_pItemINFO->IsIdentified = NormalItem.IVItItem::IsIdentified();
			out_pItemINFO->slot = NormalItem.m_slotInfo;
			out_pItemINFO->UniqueSerialNum = NormalItem.IVItItem::GetUniqueIdentityNumV2();
			out_pItemINFO->HireExpireDate = NormalItem.IVItItem::GetHireExpireDate();
		}
	}

	CITP* itp = g_itpMgr.CITPMgr::GetITP(out_pItemINFO->ITID);
	if( itp == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "item DBValueParser: invalid ITID");
		return FALSE;
	}

	out_pItemINFO->ServerItemType = INVENTORYITEMTYPE_NORMALITEM;
	out_pItemINFO->Type = itp->GetType();
	out_pItemINFO->IsDamaged = 0;
	out_pItemINFO->refiningLevel = 0;
	return TRUE;
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__DBValueParserV4_INVENTORYITEMTYPE_NORMALARROWITEM(EXEPATH(), "CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_NORMALARROWITEM");
int CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_NORMALARROWITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer) // 10520-10583
{
	int result;
	void* hookptr = CPCItemInventoryMgr__DBValueParserV4_INVENTORYITEMTYPE_NORMALARROWITEM;
	__asm push in_pIBDBuffer
	__asm mov esi, out_pItemINFO
	__asm push in_Version
	__asm call hookptr
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__DBValueParserV4_INVENTORYITEMTYPE_EQUIPITEM(EXEPATH(), "CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_EQUIPITEM");
int CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_EQUIPITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer) // 10587-10664
{
	int result;
	void* hookptr = CPCItemInventoryMgr__DBValueParserV4_INVENTORYITEMTYPE_EQUIPITEM;
	__asm mov ecx, in_pIBDBuffer
	__asm mov edi, out_pItemINFO
	__asm push in_Version
	__asm call hookptr
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__DBValueParserV4_INVENTORYITEMTYPE_CASHPOINTITEM(EXEPATH(), "CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_CASHPOINTITEM");
int CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_CASHPOINTITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer) // 10669-10713
{
	int result;
	void* hookptr = CPCItemInventoryMgr__DBValueParserV4_INVENTORYITEMTYPE_CASHPOINTITEM;
	__asm push in_pIBDBuffer
	__asm mov esi, out_pItemINFO
	__asm push in_Version
	__asm call hookptr
	return result; //TODO
}


BOOL CPCItemInventoryMgr::DBValueParserV4(CommonItemInfo* out_pItemINFO, char* in_pBuffer, const int in_BufferBytes) // 10719-10751
{
	if( in_BufferBytes <= 0 )
	{
		out_pItemINFO->ITID = 0;
		return TRUE;
	}

	unsigned short version = *(unsigned short*)(in_pBuffer + 0);
	if( version < 1 || version > 4 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "item DBValueParser: invalid versioninfo");
		return FALSE;
	}

	unsigned short type = *(unsigned short*)(in_pBuffer + 2);
	char* buffer = in_pBuffer + 4;

	if( type == INVENTORYITEMTYPE_NORMALITEM )
		return CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_NORMALITEM(version, out_pItemINFO, buffer);
	else
	if( type == INVENTORYITEMTYPE_NORMALARROWITEM )
		return CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_NORMALARROWITEM(version, out_pItemINFO, buffer);
	else
	if( type == INVENTORYITEMTYPE_EQUIPITEM )
		return CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_EQUIPITEM(version, out_pItemINFO, buffer);
	else
	if( type == INVENTORYITEMTYPE_CASHPOINTITEM )
		return CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_CASHPOINTITEM(version, out_pItemINFO, buffer);
	else
	{
		return FALSE;
	}
}


BOOL CPCItemInventoryMgr::DBValueParser(CommonItemInfo* item, char* buf, int len) // 10754-10760
{
	return CPCItemInventoryMgr::DBValueParserV4(item, buf, len);
}


hook_func<void (__stdcall *)()> CPCItemInventoryMgr__NotifyItemInfo(EXEPATH(), "CPCItemInventoryMgr::NotifyItemInfo");
void CPCItemInventoryMgr::NotifyItemInfo(const unsigned long in_Type) // 11113-11154
{
	void* hookptr = CPCItemInventoryMgr__NotifyItemInfo;
	__asm push in_Type
	__asm push this
	__asm call hookptr
	return; //TODO
/*
	CVarLenPacketPtr<PACKET_ZC_NORMAL_ITEMLIST3,16300> NormalItemPacketPtr;
	CVarLenPacketPtr<PACKET_ZC_EQUIPMENT_ITEMLIST3,16300> EquipItemPacketPtr;

	if( in_Type == BODY )
	{
		m_bodyItem.CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(NormalItemPacketPtr.GetVector());
		m_equipedItem.CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(NormalItemPacketPtr.GetVector());
		m_bodyItem.CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(EquipItemPacketPtr.GetVector(), true);
		m_equipedItem.CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(EquipItemPacketPtr.GetVector(), false);
		NormalItemPacketPtr->PacketType = HEADER_ZC_NORMAL_ITEMLIST3;
		EquipItemPacketPtr->PacketType = HEADER_ZC_EQUIPMENT_ITEMLIST3;
	}
	else
	if( in_Type == CART )
	{
		m_cartItem.CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(NormalItemPacketPtr.GetVector());
		m_cartItem.CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(EquipItemPacketPtr.GetVector(), false);
		NormalItemPacketPtr->PacketType = HEADER_ZC_CART_NORMAL_ITEMLIST3;
		EquipItemPacketPtr->PacketType = HEADER_ZC_CART_EQUIPMENT_ITEMLIST3;
	}
	else
	if( in_Type == STORE )
	{
		m_storeItem.CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(NormalItemPacketPtr.GetVector());
		m_storeItem.CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(EquipItemPacketPtr.GetVector(), false);
		NormalItemPacketPtr->PacketType = HEADER_ZC_STORE_NORMAL_ITEMLIST3;
		EquipItemPacketPtr->PacketType = HEADER_ZC_STORE_EQUIPMENT_ITEMLIST3;
	}
	else
	{
		return;
	}

	if( NormalItemPacketPtr.size() > 4 )
	{
		NormalItemPacketPtr->Length = static_cast<short>(NormalItemPacketPtr.size());
		m_owner->Send(NormalItemPacketPtr->Length, (char*)NormalItemPacketPtr);
	}

	if( EquipItemPacketPtr.size() > 4 )
	{
		EquipItemPacketPtr->Length = static_cast<short>(EquipItemPacketPtr.size());
		m_owner->Send(EquipItemPacketPtr->Length, (char*)EquipItemPacketPtr);
	}
*/
}
