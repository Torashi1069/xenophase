#include "ITP.h"
#include "ITPMgr.h"
#include "PCBodyItemIV.h"
#include "PCItemInventoryMgr.h"
#include "RuneItemInfo.h"
#include "ZoneProcess.h"
#include "shared/shared.h"


CPCBodyItemIV::CPCBodyItemIV()
{
}


CPCBodyItemIV::~CPCBodyItemIV()
{
}


IVItItem* CPCBodyItemIV::Add(IVItItem* item, int par1, BOOL isIndexChangable)
{
	if( item == NULL )
		return NULL;

	CITP* itp = g_itpMgr.CITPMgr::GetITP(item->InventoryItem::GetID());
	if( itp == NULL )
		return NULL;

	bool addQuestCount = false;

	unsigned short type = itp->GetType();
	switch( type )
	{
	case TYPE_ARROW:
	case TYPE_AMMO: 
	case TYPE_THROWWEAPON:
	case TYPE_CANNONBALL:
	{
		IVItItem* arrowItem = m_owner->CPCItemInventoryMgr::GetEquipedArrow();
		if( arrowItem != NULL && item->InventoryItem::GetID() == arrowItem->InventoryItem::GetID() )
		{
			item->IVItItem::SetIndex(arrowItem->IVItItem::GetIndex());
			return m_owner->CPCItemInventoryMgr::Add(item, 4, LOCATION_ARROW, 1, 0);
		}
	}
	break;
	case TYPE_QUEST:
	{
		if( !this->CPCItemInventory::SearchItemByID(item->InventoryItem::GetID(), false) )
		{
			if( m_questItemCount >= 1000 )
			{
				Trace("Quest Item overflow %d", m_questItemCount);
				return NULL;
			}

			addQuestCount = true;
		}
	}
	break;
	};

	IVItItem* newItem = this->CPCItemInventory::Add(item, par1, isIndexChangable);
	if( newItem == NULL )
		return NULL;

	if( type == TYPE_QUEST && addQuestCount )
		++m_questItemCount;

	m_owner->CPCItemInventoryMgr::HireItemCheckAdd(BODY, newItem);

	return newItem;
}


BOOL CPCBodyItemIV::IdentifyItem(short index)
{
	IVItItem* item = this->CPCItemInventory::SearchItemByIndex(index);
	if( item == NULL )
		return FALSE;
	
	if( item->GetType() != INVENTORYITEMTYPE_EQUIPITEM )
		return FALSE;
	
	if( item->IVItItem::IsIdentified() )
		return FALSE;

	item->IVItItem::SetIdentifyflag(true);
	return TRUE;
}


BOOL CPCBodyItemIV::Delete(short index)
{
	IVItItem* item = this->CPCItemInventory::SearchItemByIndex(index);
	if( item == NULL )
		return FALSE;
	
	CITP* itp = g_itpMgr.CITPMgr::GetITP(item->InventoryItem::GetID());
	if( itp == NULL )
		return FALSE;

	if( itp->GetType() == TYPE_QUEST )
	{
		--m_questItemCount;
		if( m_questItemCount < 0 )
			m_questItemCount = 0;
	}

	return this->CPCItemInventory::Delete(index);
}


BOOL CPCBodyItemIV::Delete(short index, short count)
{
	IVItItem* item = this->CPCItemInventory::SearchItemByIndex(index);
	if( item == NULL )
		return FALSE;
	
	CITP* itp = g_itpMgr.CITPMgr::GetITP(item->InventoryItem::GetID());
	if( itp == NULL )
		return FALSE;

	if( itp->GetType() == TYPE_QUEST && item->IVItItem::GetCount() == count )
	{
		--m_questItemCount;
		if( m_questItemCount < 0 )
			m_questItemCount = 0;
	}

	return this->CPCItemInventory::Delete(index, count);
}


void CPCBodyItemIV::Init()
{
	m_questItemCount = 0;
	this->CPCItemInventory::Init();
}


void CPCBodyItemIV::Reset()
{
	m_questItemCount = 0;
	this->CPCItemInventory::Reset();
}


int CPCBodyItemIV::GetSize()
{
	return m_itemData.size() - m_questItemCount;
}


std::vector<short> CPCBodyItemIV::GetIsMergeItemList()
{
	std::vector<short> result;

	struct stMergItemList
	{
		unsigned short wITID;
		short sIndex;

	//	BOOL operator==(const stMergItemList& );
		stMergItemList(const unsigned short in_wITID, const short in_sIndex) : wITID(in_wITID), sIndex(in_sIndex) { }
	};
	std::vector<stMergItemList> MegerItemList;

	for( std::vector<IVItItem*>::iterator iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		IVItItem* item = *iter;

		if( g_runeItemInfo.CRuneItemInfo::GetRuneItemMaxCount(item->InventoryItem::GetID()) > 0 )
			continue;

		if( item->GetType() != INVENTORYITEMTYPE_NORMALITEM && item->GetType() != INVENTORYITEMTYPE_NORMALARROWITEM )
			continue;

		if( item->IVItItem::GetUniqueIdentityNumV2() == 0 )
			continue;

		if( item->IVItItem::GetHireExpireDate() > 0 )
			continue;

		if( g_NotDisappearAfterUsingItemList.CItemListV2::IsPartOfItemList(item->InventoryItem::GetID()) )
			continue;

		MegerItemList.push_back(stMergItemList(item->InventoryItem::GetID(), item->IVItItem::GetIndex()));
	}

	for( std::vector<stMergItemList>::iterator iter = MegerItemList.begin(); iter != MegerItemList.end(); ++iter )
	{
		int count = 0;

		for( std::vector<stMergItemList>::iterator iter2 = MegerItemList.begin(); iter2 != MegerItemList.end(); ++iter2 )
			if( iter2->wITID == iter->wITID )
				++count;

		if( count > 1 )
			result.push_back(iter->sIndex);
	}

	return result;
}
