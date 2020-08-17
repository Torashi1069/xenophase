#include "ErrorLog.h"
#include "PCItemInventory.h"
#include "InventoryItem.hpp"
#include "CITP.hpp"
#include "CITPMgr.hpp"
#include "PC.h"
#include "globals.hpp"


CPCItemInventory::CPCItemInventory(void) // line 20
{
}


CPCItemInventory::~CPCItemInventory(void) // line 24
{
}


hook_method<void (CPCItemInventory::*)(void)> CPCItemInventory::_Init(SERVER, "CPCItemInventory::Init");
void CPCItemInventory::Init(void) // line 28
{
	return (this->*_Init)();

	//TODO
}


hook_method<IVItItem* (CPCItemInventory::*)(IVItItem* item, int par1, int isIndexChangable)> CPCItemInventory::_Add(SERVER, "CPCItemInventory::Add");
IVItItem* CPCItemInventory::Add(IVItItem* item, int par1, int isIndexChangable) // line 55
{
	return (this->*_Add)(item, par1, isIndexChangable);

	//TODO
}


hook_method<int (CPCItemInventory::*)(short index, short count)> CPCItemInventory::_Delete2(SERVER, "?Delete@CPCItemInventory@@UAEHFF@Z");
int CPCItemInventory::Delete(short index, short count) // line 321
{
	return (this->*_Delete2)(index, count);

	//TODO
}


hook_method<int (CPCItemInventory::*)(short index)> CPCItemInventory::_Delete3(SERVER, "?Delete@CPCItemInventory@@UAEHF@Z");
int CPCItemInventory::Delete(short index) // line 299
{
	return (this->*_Delete3)(index);

	//TODO
}


hook_method<IVItItem* (CPCItemInventory::*)(short index, short count)> CPCItemInventory::_Remove(SERVER, "CPCItemInventory::Remove");
IVItItem* CPCItemInventory::Remove(short index, short count) // line 363
{
	return (this->*_Remove)(index, count);

	//TODO
}


hook_method<int (CPCItemInventory::*)(char* out_pBuffer, const int in_MaxBytes)> CPCItemInventory::_GetAllNormalItemInfoWithBinaryFormat3(SERVER, "CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3");
int CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(char* out_pBuffer, const int in_MaxBytes) // line 531
{
	return (this->*_GetAllNormalItemInfoWithBinaryFormat3)(out_pBuffer, in_MaxBytes);

	//TODO
}


hook_method<int (CPCItemInventory::*)(char* out_pBuffer, const int in_MaxBytes, const bool in_bPet)> CPCItemInventory::_GetAllEquipedItemInfoWithBinaryFormat3(SERVER, "CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3");
int CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(char* out_pBuffer, const int in_MaxBytes, const bool in_bPet) // line 839-920
{
	return (this->*_GetAllEquipedItemInfoWithBinaryFormat3)(out_pBuffer, in_MaxBytes, in_bPet);

	#pragma pack(push,1)
	struct ITEM
	{
		/* this+ 0 */ short index;
		/* this+ 2 */ unsigned short ITID;
		/* this+ 4 */ unsigned char type;
		/* this+ 5 */ bool IsIdentified;
		/* this+ 6 */ short location;
		/* this+ 8 */ short wearLocation;
		/* this+10 */ unsigned char isDamaged;
		/* this+11 */ unsigned char refiningLevel;
		/* this+12 */ EQUIPSLOTINFO slot;
		/* this+20 */ long HireExpireDate;
		/* this+24 */ short isBind;
	};
	#pragma pack(pop)

	ITEM* p = reinterpret_cast<ITEM*>(out_pBuffer);
	int used_bytes = 0;

	mystd::vector<IVItItem*>::const_iterator iter;
	for( iter = m_itemData.begin(); iter != m_itemData.end(); ++iter )
	{
		if( used_bytes + (int)sizeof(ITEM) > in_MaxBytes )
		{
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(__FILE__, __LINE__, "SIZE OVER");
			break; // error.
		}

		IVItItem* item = *iter;
		if( item == NULL )
		{
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(__FILE__, __LINE__, "container is NULL");
			break; // error.
		}

		if( item->GetType() != INVENTORYITEMTYPE_EQUIPITEM )
			continue; // skip

		IVItEquipItem* equipitem = static_cast<IVItEquipItem*>(item);
		CITP* itp = g_itpMgr->CITPMgr::GetITP(equipitem->m_ID);
		if( itp == NULL )
			break; // error.

		p->ITID = equipitem->m_ID;
		p->isDamaged = equipitem->m_isDamaged;
		p->IsIdentified = equipitem->m_isIdentified;
		p->refiningLevel = equipitem->IVItEquipItem::GetRefiningLevel();
		p->type = static_cast<unsigned char>(itp->GetType());
		p->index = equipitem->m_index;
		p->wearLocation = equipitem->m_wearState;
		memcpy(&p->slot, &equipitem->m_slotInfo, sizeof(EQUIPSLOTINFO));
		p->HireExpireDate = equipitem->m_hire_expire_date;
		p->isBind = 0;

		if( !itp->IsApparel() )
			break; // error.

		Request reqJob;
		reqJob.Request::SetID(6);
		reqJob.par1 = 19;
		m_owner->CPCItemInventoryMgr::OnMediatorRequest(&reqJob);

		p->location = itp->GetLocation(reqJob.par2);
		if( itp->m_isBindOnEquip )
			p->isBind = ( equipitem->m_isBind != false ) + 1;

		++p;
		used_bytes += sizeof(ITEM);
	}

	if( iter != m_itemData.end() )
	{// premature abort because of error
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(__FILE__, __LINE__, "used_bytes=%d", used_bytes);

		if( m_owner != NULL )
		{
			CPC* pc = m_owner->CPCItemInventoryMgr::GetPC();
			if( pc != NULL )
				g_errorLogs->CErrorLog::CriticalErrorLogFmt(__FILE__, __LINE__, "found m_itemData container is NULL AID(%d) GID(%d) num=%d", pc->GetAccountID(), pc->CPC::GetCharacterID(), m_itemData.size());
		}

		// failure.
		return 0;
	}

	// success.
	return used_bytes;
}


hook_method<int (CPCItemInventory::*)(Request* request)> CPCItemInventory::_OnRequest(SERVER, "CPCItemInventory::OnRequest");
int CPCItemInventory::OnRequest(Request* request) // line ???
{
	return (this->*_OnRequest)(request);

	return 0;
}


hook_method<int (CPCItemInventory::*)(void)> CPCItemInventory::_GetSize(SERVER, "CPCItemInventory::GetSize");
int CPCItemInventory::GetSize(void) // line 78 (PCItemInventory.h)
{
	return (this->*_GetSize)();

	//TODO
}


hook_method<IVItItem* (CPCItemInventory::*)(short index)> CPCItemInventory::_SearchItemByIndex(SERVER, "CPCItemInventory::SearchItemByIndex");
IVItItem* CPCItemInventory::SearchItemByIndex(short index) // line 226
{
	return (this->*_SearchItemByIndex)(index);

	//TODO
}


hook_method<IVItItem* (CPCItemInventory::*)(unsigned short ITID, bool in_IsIdentified)> CPCItemInventory::_SearchItemByID(SERVER, "CPCItemInventory::SearchItemByID");
IVItItem* CPCItemInventory::SearchItemByID(unsigned short ITID, bool in_IsIdentified) // line 240
{
	return (this->*_SearchItemByID)(ITID, in_IsIdentified);

	mystd::vector<IVItItem*>::iterator it;

	for( it = m_itemData.begin(); it != m_itemData.end(); ++it )
		if( (*it)->m_ID == ITID && (!in_IsIdentified || in_IsIdentified && (*it)->m_isIdentified) )
			break;

	return( it != m_itemData.end() ) ? *it : NULL;
}


//hook_method<mystd::vector<IVItItem*>::iterator (CPCItemInventory::*)(void)> CPCItemInventory::_GetDataBeginIterator(SERVER, "CPCItemInventory::GetDataBeginIterator");
mystd::vector<IVItItem*>::iterator CPCItemInventory::GetDataBeginIterator(void)
{
//	return (this->*_GetDataBeginIterator)();

	return m_itemData.begin();
}


//hook_method<mystd::vector<IVItItem*>::iterator (CPCItemInventory::*)(void)> CPCItemInventory::_GetDataEndIterator(SERVER, "CPCItemInventory::GetDataEndIterator");
mystd::vector<IVItItem*>::iterator CPCItemInventory::GetDataEndIterator(void)
{
//	return (this->*_GetDataEndIterator)();

	return m_itemData.end();
}


hook_method<void (CPCItemInventory::*)(void)> CPCItemInventory::_Reset(SERVER, "CPCItemInventory::Reset");
void CPCItemInventory::Reset(void) // line 43
{
	return (this->*_Reset)();

	//TODO
}
