#include "Player/Inventory/CIVItNormalItem.h"


IVItNormalItem::IVItNormalItem()
{
	this->IVItNormalItem::InitReal();
}


IVItNormalItem::~IVItNormalItem()
{
}


void IVItNormalItem::InitReal()
{
	this->IVItItem::InitReal();
	m_isIdentified = true;
}


void IVItNormalItem::InitVirtual()
{
	this->IVItNormalItem::InitReal();
}


unsigned long IVItNormalItem::GetType()
{
	return INVENTORYITEMTYPE_NORMALITEM;
}


void IVItNormalItem::CopyFromParData(IVItItemData* data)
{
	IVItNormalItemData* pData = static_cast<IVItNormalItemData*>(data);
	m_ID = pData->ITID;
	m_isIdentified = pData->IsIdentified;
	m_count = pData->count;
	memcpy_s(&m_slotInfo, sizeof(m_slotInfo), &pData->slot, sizeof(pData->slot));
}


void IVItNormalItem::CopyToParData(IVItItemData* data)
{
	IVItNormalItemData* pData = static_cast<IVItNormalItemData*>(data);
	pData->ITID = m_ID;
	pData->IsIdentified = m_isIdentified;
	pData->count = m_count;
	memcpy_s(&pData->slot, sizeof(pData->slot), &m_slotInfo, sizeof(m_slotInfo));
}


void IVItNormalItem::CopyFromOtherItem(IVItItem* item)
{
	IVItNormalItem* pItem = static_cast<IVItNormalItem*>(item);
	m_ID = item->InventoryItem::GetID();
	m_isIdentified = item->IVItItem::IsIdentified();
	m_count = item->IVItItem::GetCount();
	memcpy_s(&m_slotInfo, sizeof(m_slotInfo), &item->m_slotInfo, sizeof(item->m_slotInfo));
	this->IVItItem::SetUniqueIdentityNumV2(item->IVItItem::GetUniqueIdentityNumV2());
	this->IVItItem::SetHireExpireDate(item->IVItItem::GetHireExpireDate());
}


int IVItNormalItem::IBData_Set(char* in_pIBDBuffer)
{
	char* pBuffer = in_pIBDBuffer;
	int result = 0;

	IVItNormalItemDataV2* pData = reinterpret_cast<IVItNormalItemDataV2*>(in_pIBDBuffer);
	m_ID = pData->ITID;
	m_isIdentified = pData->Flag.IsIdentified;
	m_count = pData->count;
	memcpy_s(&m_slotInfo, sizeof(m_slotInfo), &pData->slot, sizeof(pData->slot));
	m_isBind = pData->Flag.IsBind;
	pData += sizeof(IVItNormalItemDataV2);
	result += sizeof(IVItNormalItemDataV2);

	int AdditionalLen = this->IVItItem::IBData_Load_AdditionalElement(pData->Flag, pBuffer);
	pData += AdditionalLen;
	result += AdditionalLen;

	return result;
}


int IVItNormalItem::IBData_Get(char* in_pBuffer, const bool in_bIncType)
{
	char* pBuffer = in_pBuffer;
	int result = 0;

	int TypeLen = this->IVItItem::IBData_Save_Type(in_pBuffer, in_bIncType);
	pBuffer += TypeLen;
	result += TypeLen;

	IVItNormalItemDataV2* pData = reinterpret_cast<IVItNormalItemDataV2*>(pBuffer);
	pData->ITID = m_ID;
	pData->Flag.clear();
	pData->Flag.IsIdentified = m_isIdentified;
	pData->Flag.IsBind = m_isBind;
	if( m_unique_identity_number != 0 )
		pData->Flag.exist_unique_identity_number |= true;
	if( m_hire_expire_date != 0 )
		pData->Flag.exist_hire_expire_date |= true;
	pData->count = m_count;
	memcpy_s(&pData->slot, sizeof(pData->slot), &m_slotInfo, sizeof(m_slotInfo));
	pBuffer += sizeof(IVItNormalItemDataV2);
	result += sizeof(IVItNormalItemDataV2);

	int AdditionalLen = this->IVItItem::IBData_Save_AdditionalElement(pBuffer, pData->Flag);
	pBuffer += AdditionalLen;
	result += AdditionalLen;

	return result;
}
