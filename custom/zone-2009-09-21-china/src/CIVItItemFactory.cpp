#include "CIVItItemFactory.hpp"


hook_method<void (CIVItItemFactory::*)(InventoryItem* item)> CIVItItemFactory::_FreeInventoryItem(SERVER, "CIVItItemFactory::FreeInventoryItem");


void CIVItItemFactory::FreeInventoryItem(InventoryItem* item)
{
	return (this->*_FreeInventoryItem)(item);

	if( item == NULL )
		return;

	switch( item->GetType() )
	{
	case INVENTORYITEMTYPE_NORMALITEM:
		m_NIMPool.CMemoryMgr<IVItNormalItem>::Free((IVItNormalItem *)item);
		break;
	case INVENTORYITEMTYPE_NORMALARROWITEM:
		m_NAIMPool.CMemoryMgr<IVItNormalArrowItem>::Free((IVItNormalArrowItem *)item);
		break;
	case INVENTORYITEMTYPE_EQUIPITEM:
		m_EIMPool.CMemoryMgr<IVItEquipItem>::Free((IVItEquipItem *)item);
		break;
	case INVENTORYITEMTYPE_QUESTITEM:
		m_QIMPool.CMemoryMgr<IVItQuestItem>::Free((IVItQuestItem *)item);
		break;
	case INVENTORYITEMTYPE_CASHPOINTITEM:
		m_CPIPool.CMemoryMgr<IVItCashPointItem>::Free((IVItCashPointItem *)item);
		break;
	default:
		break;
	}
}


hook_method<void (CIVItItemFactory::*)(void)> CIVItItemFactory::_Init(SERVER, "CIVItItemFactory::Init");
void CIVItItemFactory::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CIVItItemFactory::*)(void)> CIVItItemFactory::_Reset(SERVER, "CIVItItemFactory::Reset");
void CIVItItemFactory::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<IVItItem* (CIVItItemFactory::*)(unsigned short ID, short count)> CIVItItemFactory::_AllocInventoryItem(SERVER, "CIVItItemFactory::AllocInventoryItem");
IVItItem* CIVItItemFactory::AllocInventoryItem(unsigned short ID, short count)
{
	return (this->*_AllocInventoryItem)(ID, count);

	//TODO
}
