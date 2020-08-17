#include "Player/Inventory/CIVItItem.h"
#include "shared/NCriticalErrorLog.h"


IVItItem::IVItItem()
{
	this->IVItItem::InitReal();
}


void IVItItem::InitReal()
{
	this->InventoryItem::SetID(0);
	m_isIdentified = false;
	m_isBind = false;
	m_count = 1;
	m_unique_identity_number = 0;
	m_hire_expire_date = 0;
	m_slotInfo.info[0] = 0;
	m_slotInfo.info[1] = 0;
	m_slotInfo.info[2] = 0;
	m_slotInfo.info[3] = 0;
	m_index = -1;
}


void IVItItem::InitVirtual()
{
	this->IVItItem::InitReal();
}


unsigned long IVItItem::GetType()
{
	return INVENTORYITEMTYPE_ITEM;
}


bool IVItItem::IsIdentified()
{
	return m_isIdentified;
}


void IVItItem::SetIdentifyflag(bool flag)
{
	m_isIdentified = flag;
}


short IVItItem::GetCount()
{
	return m_count;
}


void IVItItem::SetCount(short count)
{
	m_count = count;
}


void IVItItem::AddCount(short count)
{
	m_count += count;
}


void IVItItem::SetIndex(unsigned short index)
{
	m_index = index;
}


short IVItItem::GetIndex()
{
	return m_index;
}


bool IVItItem::IsBind()
{
	return m_isBind;
}


void IVItItem::SetBind(bool flag)
{
	m_isBind = flag;
}


void IVItItem::SetSlotInfo(EQUIPSLOTINFO* par)
{
	m_slotInfo = *par;
}


EQUIPSLOTINFO* IVItItem::GetSlotInfo()
{
	return &m_slotInfo;
}


unsigned long IVItItem::GetMakerGID()
{
	return (m_slotInfo.info[2] << 0) | (m_slotInfo.info[3] << 16);
}


void IVItItem::SetUniqueIdentityNumV2(const __int64 in_unique_identity_number)
{
	m_unique_identity_number = in_unique_identity_number;
}


__int64 IVItItem::GetUniqueIdentityNumV2()
{
	return m_unique_identity_number;
}


void IVItItem::SetHireExpireDate(const time_t in_hire_expire_date)
{
	time_t hire_expire_date = in_hire_expire_date;
	if( hire_expire_date < 0 )
		hire_expire_date = time(NULL) + 10000;

	m_hire_expire_date = hire_expire_date;
}


time_t IVItItem::GetHireExpireDate()
{
	return m_hire_expire_date;
}


int IVItItem::IBData_Set(char* in_pIBDBuffer)
{
	return 0;
}


bool IVItItem::IsMapPropertyBlocked(const int in_loc)
{
	return false;
}


void IVItItem::SetMapPropertyBlocked(const int in_loc, bool flag)
{
}


int IVItItem::IBData_Get(char* in_pBuffer, const bool in_bIncType)
{
	return 0;
}


int IVItItem::IBData_Save_Type(char* in_pBuffer, const bool in_bType)
{
	if( in_bType == true )
	{
		*(unsigned short*)in_pBuffer = static_cast<unsigned short>(this->GetType());
		return 2;
	}
	else
	{
		return 0;
	}
}


int IVItItem::IBData_Load_AdditionalElement(const IVItItemDataV2::tagFlag in_Flag, char* in_pBuffer)
{
	char* pBuffer = in_pBuffer;
	int result = 0;

	if( in_Flag.exist_unique_identity_number )
	{
		m_unique_identity_number = *(__int64*)pBuffer;
		pBuffer += sizeof(__int64);
		result += sizeof(__int64);
	}

	if( in_Flag.exist_hire_expire_date )
	{
		m_hire_expire_date = *(time_t*)pBuffer;
		pBuffer += sizeof(time_t);
		result += sizeof(time_t);
	}

	return result;
}


int IVItItem::IBData_Save_AdditionalElement(char* in_pBuffer, const IVItItemDataV2::tagFlag in_Flag)
{
	char* pBuffer = in_pBuffer;
	int result = 0;

	if( in_Flag.exist_unique_identity_number )
	{
		*(__int64*)pBuffer = m_unique_identity_number;
		pBuffer += sizeof(__int64);
		result += sizeof(__int64);
	}

	if( in_Flag.exist_hire_expire_date )
	{
		*(time_t*)pBuffer = m_hire_expire_date;
		pBuffer += sizeof(time_t);
		result += sizeof(time_t);
	}

	return result;
}


void IVItItem::CopyFromParData(IVItItemData* data)
{
	//TODO
	/*
	IVItNormalItemData* ptr = static_cast<IVItNormalItemData*>(data);
	this->InventoryItem::SetID(ptr->ITID);
	m_isIdentified = ptr->IsIdentified;
	m_count = ptr->count;
	m_slotInfo = ptr->slot;
	*/
}


void IVItItem::CopyToParData(IVItItemData* data)
{
	//TODO
	/*
	IVItNormalItemData* ptr = static_cast<IVItNormalItemData*>(data);
	ptr->ITID = this->InventoryItem::GetID();
	ptr->IsIdentified = m_isIdentified;
	ptr->count = m_count;
	ptr->slot = m_slotInfo;
	*/
}


void IVItItem::CopyFromOtherItem(IVItItem* item)
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "No Entering! ITID(%d)", item->InventoryItem::GetID());

	this->InventoryItem::SetID(item->InventoryItem::GetID());
	m_isIdentified = item->m_isIdentified;
	m_count = item->m_count;
	memcpy_s(&m_slotInfo, sizeof(m_slotInfo), &item->m_slotInfo, sizeof(item->m_slotInfo));
	this->IVItItem::SetUniqueIdentityNumV2(item->m_unique_identity_number);
	this->IVItItem::SetHireExpireDate(item->m_hire_expire_date);
}


int IVItItem::IsMovable()
{
	return 0;
	//TODO
	/*
	if( m_isBind == true )
		return NOTMOVE_ALL & ~NOTMOVE_SELL_NPC;

	CITP* itp = g_itpMgr.CITPMgr::GetITP(this->InventoryItem::GetID());
	if ( itp == NULL )
		return NOTMOVE_ALL;

	return itp->IsMovable();
	*/
}
