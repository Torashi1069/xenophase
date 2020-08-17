#include "ITPMgr.h"
#include "ZoneProcess.h"
#include "Player/Inventory/CIVItEquipItem.h"


IVItEquipItem::IVItEquipItem()
{
	this->IVItEquipItem::InitReal();
}


IVItEquipItem::~IVItEquipItem()
{
}


void IVItEquipItem::InitReal()
{
	this->IVItItem::InitReal();
	m_isDamaged = false;
	m_refiningLevel = 0;
	m_isMapPropertyBlocked[0] = false;
	m_isMapPropertyBlocked[1] = false;
	m_isMapPropertyBlocked[2] = false;
	m_isMapPropertyBlocked[3] = false;
	m_isMapPropertyBlocked[4] = false;
	m_slotInfo.info[0] = 0;
	m_slotInfo.info[1] = 0;
	m_slotInfo.info[2] = 0;
	m_slotInfo.info[3] = 0;
	m_wearState = 0;
}


void IVItEquipItem::InitVirtual()
{
	this->IVItEquipItem::InitReal();
}


unsigned long IVItEquipItem::GetType()
{
	return INVENTORYITEMTYPE_EQUIPITEM;
}


void IVItEquipItem::SetIdentifyNumber(const __int64 in_unique_identity_number)
{
	this->IVItItem::SetUniqueIdentityNumV2(in_unique_identity_number);
}


__int64 IVItEquipItem::GetIdentifyNumber() const
{
	return m_unique_identity_number;
}


void IVItEquipItem::SetDamageFlag(bool flag)
{
	m_isDamaged = flag;
}


bool IVItEquipItem::IsDamaged() const
{
	return m_isDamaged;
}


void IVItEquipItem::SetRefiningLevel(unsigned char level)
{
	m_refiningLevel = level;
}


unsigned char IVItEquipItem::GetRefiningLevel() const
{
	if( m_refiningLevel > 20 )
		return 0;

	return m_refiningLevel;
}


unsigned short IVItEquipItem::GetWearState() const
{
	return m_wearState;
}


void IVItEquipItem::SetWearState(unsigned short wearState)
{
	m_wearState = wearState;
}


void IVItEquipItem::AddCardToSlot(unsigned short ITID)
{
	for( size_t i = 0; i < countof(m_slotInfo.info); ++i )
	{
		if( m_slotInfo.info[i] == 0 )
		{
			m_slotInfo.info[i] = ITID;
			break; // done.
		}
	}
}


BOOL IVItEquipItem::IsSlotAvailable()
{
	CITP* itp = g_itpMgr.CITPMgr::GetITP(m_ID);
	if( itp == NULL )
		return FALSE;

	if( m_slotInfo.info[0] == BLACKSMITH_ITEM_VERSION || m_slotInfo.info[0] == NAMED_ITEM_VERSION )
		return FALSE;

	for( int i = 0; i < itp->GetMaxSlot() && i < countof(m_slotInfo.info); ++i )
		if( m_slotInfo.info[i] == 0 )
			return TRUE; // found.

	return FALSE; // not found.
}


bool IVItEquipItem::IsMapPropertyBlocked(const int in_loc)
{
	return m_isMapPropertyBlocked[in_loc];
}


void IVItEquipItem::SetMapPropertyBlocked(const int in_loc, bool flag)
{
	m_isMapPropertyBlocked[in_loc] = flag;
}


void IVItEquipItem::CopyFromParData(IVItItemData* data)
{
	IVItEquipItemData* pData = static_cast<IVItEquipItemData*>(data);
	m_ID = pData->ITID;
	m_isIdentified = pData->IsIdentified;
	this->IVItItem::SetUniqueIdentityNumV2(pData->IdentifyNumber);
	m_wearState = pData->WearState;
	m_isDamaged = pData->IsDamaged;
	m_refiningLevel = pData->RefiningLevel;
	memcpy_s(&m_slotInfo, sizeof(m_slotInfo), &pData->slot, sizeof(pData->slot));
}


void IVItEquipItem::CopyToParData(IVItItemData* data)
{
	IVItEquipItemData* pData = static_cast<IVItEquipItemData*>(data);
	pData->ITID = m_ID;
	pData->IsIdentified = m_isIdentified;
	pData->IdentifyNumber = static_cast<int>(this->IVItItem::GetUniqueIdentityNumV2());
	pData->WearState = m_wearState;
	pData->IsDamaged = m_isDamaged;
	pData->RefiningLevel = this->IVItEquipItem::GetRefiningLevel();
	memcpy_s(&pData->slot, sizeof(pData->slot), &m_slotInfo, sizeof(m_slotInfo));
}


void IVItEquipItem::CopyFromOtherItem(IVItItem* item)
{
	IVItEquipItem* pItem = static_cast<IVItEquipItem*>(item);
	m_ID = pItem->m_ID;
	m_isIdentified = pItem->m_isIdentified;
	this->IVItItem::SetUniqueIdentityNumV2(pItem->m_unique_identity_number);
	m_wearState = pItem->m_wearState;
	m_isDamaged = pItem->m_isDamaged;
	m_refiningLevel = pItem->IVItEquipItem::GetRefiningLevel();
	memcpy_s(&m_slotInfo, sizeof(m_slotInfo), &pItem->m_slotInfo, sizeof(pItem->m_slotInfo));
	this->IVItItem::SetHireExpireDate(pItem->m_hire_expire_date);
}


int IVItEquipItem::IBData_Set(char* in_pIBDBuffer)
{
	char* pBuffer = in_pIBDBuffer;
	int result = 0;

	IVItEquipItemDataV2* pData = reinterpret_cast<IVItEquipItemDataV2*>(in_pIBDBuffer);
	m_ID = pData->ITID;
	m_isIdentified = pData->Flag.IsIdentified;
	m_wearState = pData->WearState;
	m_isDamaged = pData->IsDamaged;
	m_refiningLevel = pData->RefiningLevel;
	memcpy_s(&m_slotInfo, sizeof(m_slotInfo), &pData->slot, sizeof(pData->slot));
	m_isBind = pData->Flag.IsBind;
	pBuffer += sizeof(IVItEquipItemDataV2);
	result += sizeof(IVItEquipItemDataV2);

	int AdditionalLen = this->IVItItem::IBData_Load_AdditionalElement(pData->Flag, pBuffer);
	pBuffer += AdditionalLen;
	result += AdditionalLen;

	return result;
}


int IVItEquipItem::IBData_Get(char* in_pBuffer, const bool in_bIncType)
{
	char* pBuffer = in_pBuffer;
	int result = 0;

	int TypeLen = this->IVItItem::IBData_Save_Type(in_pBuffer, in_bIncType);
	pBuffer += TypeLen;
	result += TypeLen;

	IVItEquipItemDataV2* pData = reinterpret_cast<IVItEquipItemDataV2*>(pBuffer);
	pData->ITID = m_ID;
	pData->Flag.clear();
	pData->Flag.IsIdentified = m_isIdentified;
	pData->Flag.IsBind = m_isBind;
	if( m_unique_identity_number != 0 )
		pData->Flag.exist_unique_identity_number = true;
	if( m_hire_expire_date != 0 )
		pData->Flag.exist_hire_expire_date = true;
	pData->WearState = m_wearState;
	pData->IsDamaged = m_isDamaged;
	pData->RefiningLevel = this->IVItEquipItem::GetRefiningLevel();
	memcpy_s(&pData->slot, sizeof(pData->slot), &m_slotInfo, sizeof(m_slotInfo));
	pBuffer += sizeof(IVItEquipItemDataV2);
	result += sizeof(IVItEquipItemDataV2);

	int AdditionalLen = this->IVItItem::IBData_Save_AdditionalElement(pBuffer, pData->Flag);
	pBuffer += AdditionalLen;
	result += AdditionalLen;

	return result;
}
