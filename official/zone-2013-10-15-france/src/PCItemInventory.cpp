#include "ITPMgr.h"
#include "PC.h"
#include "PCItemInventory.h"
#include "PCItemInventoryMgr.h"
#include "QuestArlimi.h"
#include "ZoneProcess.h"
#include "Player/Inventory/CIVItEquipItem.h"
#include "shared/NCriticalErrorLog.h"


CPCItemInventory::CPCItemInventory()
: m_owner(NULL),
//m_indexIncrement(0),
//m_weight(0),
  m_itemData()
{
}


CPCItemInventory::~CPCItemInventory()
{
}


void CPCItemInventory::Init()
{
	m_weight = 0;
	m_indexIncrement = 1;

	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
		if( m_owner != NULL )
			m_owner->CPCItemInventoryMgr::FreeInventoryItem(*iter);

	m_itemData.clear();
	m_owner = NULL;
}


void CPCItemInventory::Reset()
{
	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		if( m_owner != NULL )
			m_owner->CPCItemInventoryMgr::FreeInventoryItem(*iter);
	}

	m_itemData.clear();
	m_weight = 0;
}


hook_func<IVItItem* (CPCItemInventory::*)(IVItItem* item, int par1, BOOL isIndexChangable)> CPCItemInventory__Add(EXEPATH(), "CPCItemInventory::Add");
IVItItem* CPCItemInventory::Add(IVItItem* item, int par1, BOOL isIndexChangable)
{
	return (this->*CPCItemInventory__Add)(item, par1, isIndexChangable); //TODO
}


BOOL CPCItemInventory::IsAlreadyExist(IVItItem* item)
{
	unsigned long itemGID = (item->m_slotInfo.info[2] << 0) | (item->m_slotInfo.info[3] << 16);
	if( this->CPCItemInventory::SearchItem(item->InventoryItem::GetID(), itemGID, item->IVItItem::GetUniqueIdentityNumV2()) == NULL )
		return FALSE;

	return TRUE;
}


IVItItem* CPCItemInventory::SearchItemByUniqueIdentityNum(const __int64 in_UID)
{
	if( in_UID == 0 )
		return NULL;

	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		if( in_UID == item->IVItItem::GetUniqueIdentityNumV2() )
			return item;
	}

	return NULL; // not found.
}


IVItItem* CPCItemInventory::SearchItemByIndex(short index)
{
	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		if( item->IVItItem::GetIndex() == index )
			return item; // found.
	}

	return NULL; // not found.
}


IVItItem* CPCItemInventory::SearchItemByID(unsigned short ITID, bool in_IsIdentified)
{
	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		if( item->InventoryItem::GetID() == ITID && (!in_IsIdentified || in_IsIdentified && item->IVItItem::IsIdentified()) )
			return item; // found.
	}

	return NULL; // not found.
}


IVItItem* CPCItemInventory::SearchItem(unsigned short ITID, unsigned long GID, const __int64 in_UID)
{
	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		unsigned long itemGID = (item->m_slotInfo.info[2] << 0) | (item->m_slotInfo.info[3] << 16);
		if( item->InventoryItem::GetID() == ITID && itemGID == GID && item->IVItItem::GetUniqueIdentityNumV2() == in_UID )
			return item; // found.
	}

	return NULL; // not found.
}


IVItItem* CPCItemInventory::SearchItemByID_GID(unsigned short ITID, unsigned long GID)
{
	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		unsigned long itemGID = (item->m_slotInfo.info[2] << 0) | (item->m_slotInfo.info[3] << 16);
		if ( item->InventoryItem::GetID() == ITID && itemGID == GID )
			return item; // found.
	}

	return NULL; // not found.
}


int CPCItemInventory::OnRequest(Request* request)
{
	return 0;
}


BOOL CPCItemInventory::Delete(short index)
{
	std::vector<IVItItem*>::iterator iter;
	for( iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
		if( (*iter)->IVItItem::GetIndex() == index )
			break;
	if( iter == m_itemData.end() )
		return FALSE;

	this->CPCItemInventory::MinusWeight((*iter)->IVItItem::GetCount() * g_itpMgr.CITPMgr::GetItemWeight((*iter)->InventoryItem::GetID()));
	m_owner->CPCItemInventoryMgr::FreeInventoryItem(*iter);
	m_itemData.std::vector<IVItItem*>::erase(iter);
	this->CPCItemInventory::SendNotifyQuest();
	return TRUE;
}


void CPCItemInventory::DeleteAll()
{
	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); )
	{
		IVItItem* item = *iter;

		if( item != NULL && g_itpMgr.CITPMgr::GetInventoryItemType(item->InventoryItem::GetID()) != INVENTORYITEMTYPE_QUESTITEM )
		{
			this->CPCItemInventory::MinusWeight(item->IVItItem::GetCount() * g_itpMgr.CITPMgr::GetItemWeight(item->InventoryItem::GetID()));
			m_owner->CPCItemInventoryMgr::FreeInventoryItem(item);

			iter = m_itemData.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


BOOL CPCItemInventory::Delete(short index, short count)
{
	if( count < 0 )
		return FALSE;

	std::vector<IVItItem*>::iterator iter;
	for( iter = m_itemData.begin(); iter == m_itemData.end(); ++iter )
		if( (*iter)->IVItItem::GetIndex() == index )
			break;
	if( iter == m_itemData.end() )
		return FALSE;

	IVItItem* item = *iter;
	if( item->IVItItem::GetCount() == count )
	{
		this->CPCItemInventory::MinusWeight(count * g_itpMgr.CITPMgr::GetItemWeight(item->InventoryItem::GetID()));
		m_owner->CPCItemInventoryMgr::FreeInventoryItem(item);
		m_itemData.erase(iter);
		this->CPCItemInventory::SendNotifyQuest();
		return TRUE;
	}
	else
	if( item->IVItItem::GetCount() > count )
	{
		this->CPCItemInventory::MinusWeight(count * g_itpMgr.CITPMgr::GetItemWeight(item->InventoryItem::GetID()));
		item->IVItItem::AddCount(-count);
		this->CPCItemInventory::SendNotifyQuest();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


IVItItem* CPCItemInventory::Remove(short index, short count)
{
	if( count < 0 )
		return NULL;

	this->CPCItemInventory::SendNotifyQuest();

	CPC* pc = m_owner->CPCItemInventoryMgr::GetPC();
	std::vector<IVItItem*>::iterator iter;
	for( iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		if( item->IVItItem::GetIndex() == index )
		{
			if( item->IVItItem::GetCount() == count )
			{
				m_itemData.erase(iter);
				this->CPCItemInventory::MinusWeight(count * g_itpMgr.CITPMgr::GetItemWeight(item->InventoryItem::GetID()));
				return item;
			}
			else
			if( item->IVItItem::GetCount() > count && count > 0 )
			{
				item->IVItItem::AddCount(-count);
				this->CPCItemInventory::MinusWeight(count * g_itpMgr.CITPMgr::GetItemWeight(item->InventoryItem::GetID()));

				IVItItem* newItem = m_owner->AllocInventoryItem(item->InventoryItem::GetID(), count);
				if( newItem != NULL )
				{
					newItem->m_slotInfo = item->m_slotInfo;
					newItem->IVItItem::SetIndex(index);
					newItem->IVItItem::SetUniqueIdentityNumV2(item->IVItItem::GetUniqueIdentityNumV2());
					newItem->IVItItem::SetHireExpireDate(item->IVItItem::GetHireExpireDate());
					return newItem;
				}
			}
			else
			{
				unsigned long AID;
				if( pc != NULL )
				{
					pc->AddErrorCnt(__FILE__, __LINE__, 1, timeGetTime());
					AID = pc->GetAccountID();
				}
				else
				{
					AID = 0;
				}

				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Item_Remove_Error(1) AID(%d), CallIndex(%d), ItemIndex(%d), ItemID(%d), Count(%d)", AID, index, item->IVItItem::GetIndex(), item->InventoryItem::GetID(), count);
				return NULL;
			}
		}
	}

	// iter == m_itemData.end()
	unsigned long AID;
	if( pc != NULL )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 1, timeGetTime());
		AID = pc->GetAccountID();
	}
	else
	{
		AID = 0;
	}

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Item_Remove_Error(2) AID(%d), CallIndex(%d), Count(%d)", AID, index, count);
	return NULL;
}


void CPCItemInventory::PlusWeight(int weight)
{
	m_weight += weight;
}


void CPCItemInventory::MinusWeight(int weight)
{
	m_weight -= weight;
	if( m_weight < 0 )
		m_weight = 0;
}


int CPCItemInventory::GetWeight()
{
	return m_weight;
}


int CPCItemInventory::GetSize()
{
	return m_itemData.size();
}


void CPCItemInventory::SetOwner(CPCItemInventoryMgr* owner)
{
	m_owner = owner;
}


std::vector<IVItItem*>::iterator CPCItemInventory::GetDataBeginIterator()
{
	return m_itemData.begin();
}


std::vector<IVItItem*>::iterator CPCItemInventory::GetDataEndIterator()
{
	return m_itemData.end();
}


void CPCItemInventory::GetAllItemWithDBFormat(char* in_pBuffer, int& out_size, const bool in_bSetItemType)
{
	this->CPCItemInventory::GetAllItemWithDBFormatV4(in_pBuffer, out_size, in_bSetItemType);
}


void CPCItemInventory::GetAllItemWithDBFormatV4(char* in_pBuffer, int& out_size, const bool in_bSetItemType)
{
	out_size = 0;

	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		if( item != NULL && item->InventoryItem::GetID() > 0 )
			out_size += item->IBData_Get(&in_pBuffer[out_size], in_bSetItemType);
	}
}


IVItItem* CPCItemInventory::GetFirstItem()
{
	std::vector<IVItItem*>::iterator iter = m_itemData.begin();
	if( iter == m_itemData.end() )
		return NULL;

	IVItItem* item = *iter;
	this->CPCItemInventory::MinusWeight(item->IVItItem::GetCount() * g_itpMgr.CITPMgr::GetItemWeight(item->InventoryItem::GetID()));
	m_itemData.erase(iter);

	return item;
}


IVItItem* CPCItemInventory::PeekFirstItem()
{
	std::vector<IVItItem*>::iterator iter = m_itemData.begin();
	if( iter == m_itemData.end() )
		return NULL;

	IVItItem* item = *iter;

	return item;
}


void CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(std::vector<unsigned char>& io_vecBuffer)
{
	if( m_owner == NULL )
		return;
	
	CPC* pc = m_owner->CPCItemInventoryMgr::GetPC();
	if( pc == NULL )
		return;
	
	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter == m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		if( item == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "found m_itemData container is NULL AID(%d) GID(%d) num=%d", pc->GetAccountID(), pc->CPC::GetCharacterID(), m_itemData.size());
			pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return;
		}

		unsigned long type = item->GetType();
		if( type != INVENTORYITEMTYPE_NORMALITEM && type != INVENTORYITEMTYPE_NORMALARROWITEM && type != INVENTORYITEMTYPE_CASHPOINTITEM )
			continue; // skip

		CITP* itp = g_itpMgr.CITPMgr::GetITP(item->InventoryItem::GetID());
		if( itp == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "found itp is NULL itid(%d), AID(%d) GID(%d)", item->InventoryItem::GetID(), pc->GetAccountID(), pc->CPC::GetCharacterID());
			pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return;
		}

		PACKET_ZC_NORMAL_ITEMLIST3::ITEM NotifyItem;
		NotifyItem.index = item->IVItItem::GetIndex();
		NotifyItem.ITID = item->InventoryItem::GetID();
		NotifyItem.type = static_cast<unsigned char>(itp->GetType());
		NotifyItem.count = item->IVItItem::GetCount();
		NotifyItem.IsIdentified = item->IVItItem::IsIdentified();
		NotifyItem.slot = item->m_slotInfo;
		NotifyItem.HireExpireDate = item->IVItItem::GetHireExpireDate();
		NotifyItem.WearState = ( itp->GetType() == TYPE_ARROW || itp->GetType() == TYPE_AMMO || itp->GetType() == TYPE_THROWWEAPON || itp->GetType() == TYPE_CANNONBALL ) ? LOCATION_ARROW : 0;
		io_vecBuffer.insert(io_vecBuffer.end(), (unsigned char*)&NotifyItem, ((unsigned char*)&NotifyItem) + sizeof(NotifyItem));
	}
}


void CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(std::vector<unsigned char>& io_vecBuffer, const bool in_bPet)
{
	if( m_owner == NULL )
		return;
	
	CPC* pc = m_owner->CPCItemInventoryMgr::GetPC();
	if( pc == NULL )
		return;
	
	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter == m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		if( *iter == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "found m_itemData container is NULL AID(%d) GID(%d) num=%d", pc->GetAccountID(), pc->CPC::GetCharacterID(), m_itemData.size());
			pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return;
		}

		if( item->GetType() != INVENTORYITEMTYPE_EQUIPITEM )
			continue; // skip

		IVItEquipItem* equipItem = static_cast<IVItEquipItem*>(item);

		CITP* itp = g_itpMgr.CITPMgr::GetITP(equipItem->InventoryItem::GetID());
		if( itp == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "found itp is NULL itid(%d), AID(%d) GID(%d)", equipItem->InventoryItem::GetID(), pc->GetAccountID(), pc->CPC::GetCharacterID());
			pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return;
		}

		PACKET_ZC_EQUIPMENT_ITEMLIST3::ITEM NotifyItem;
		NotifyItem.wItemSpriteNumber = itp->GetClass();
		NotifyItem.ITID = equipItem->InventoryItem::GetID();
		NotifyItem.IsDamaged = equipItem->IVItEquipItem::IsDamaged();
		NotifyItem.IsIdentified = equipItem->IVItItem::IsIdentified();
		NotifyItem.RefiningLevel = equipItem->IVItEquipItem::GetRefiningLevel();
		NotifyItem.type = static_cast<unsigned char>(itp->GetType());
		NotifyItem.index = equipItem->IVItItem::GetIndex();
		NotifyItem.WearState = equipItem->IVItEquipItem::GetWearState();
		NotifyItem.slot = equipItem->m_slotInfo;
		NotifyItem.HireExpireDate = equipItem->IVItItem::GetHireExpireDate();
		NotifyItem.bindOnEquipType = 0;

		if( !itp->IsApparel() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "found itp is NULL itid(%d), AID(%d) GID(%d)", equipItem->InventoryItem::GetID(), pc->GetAccountID(), pc->CPC::GetCharacterID());
			pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
			return;
		}

		Request reqJob;
		reqJob.Request::SetID(RT_REQ_PCVAR);
		reqJob.par1 = VAR_JOB;
		m_owner->CPCItemInventoryMgr::OnMediatorRequest(&reqJob);

		NotifyItem.location = itp->GetLocation(reqJob.par2);
		if( itp->m_isBindOnEquip == true )
			NotifyItem.bindOnEquipType = ( equipItem->IVItItem::IsBind() ) ? 1 : 2;

		io_vecBuffer.insert(io_vecBuffer.end(), (unsigned char*)&NotifyItem, ((unsigned char*)&NotifyItem) + sizeof(NotifyItem));
	}
}


void CPCItemInventory::SendNotifyQuest()
{
	if( m_owner == NULL )
		return;

	CPC* pc = m_owner->CPCItemInventoryMgr::GetPC();
	if( pc == NULL )
		return;

	g_questArlimi.CQuestArlimi::InsertPCQuest(pc->GetAccountID());
}
