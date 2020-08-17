#include "CPCEquipedItemIV.hpp"


CPCEquipedItemIV::CPCEquipedItemIV(void)
{
}


CPCEquipedItemIV::~CPCEquipedItemIV(void)
{
}


hook_method<void (CPCEquipedItemIV::*)(void)> CPCEquipedItemIV::_Init(SERVER, "CPCEquipedItemIV::Init");
void CPCEquipedItemIV::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<IVItItem* (CPCEquipedItemIV::*)(IVItItem* item, int par1, int isIndexChangable)> CPCEquipedItemIV::_Add(SERVER, "CPCEquipedItemIV::Add");
IVItItem* CPCEquipedItemIV::Add(IVItItem* item, int par1, int isIndexChangable)
{
	return (this->*_Add)(item, par1, isIndexChangable);

	//TODO
}


hook_method<int (CPCEquipedItemIV::*)(short index, short count)> CPCEquipedItemIV::_Delete(SERVER, "CPCEquipedItemIV::Delete");
int CPCEquipedItemIV::Delete(short index, short count)
{
	return (this->*_Delete)(index, count);

	//TODO
}


hook_method<IVItItem* (CPCEquipedItemIV::*)(short index, short count)> CPCEquipedItemIV::_Remove(SERVER, "CPCEquipedItemIV::Remove");
IVItItem* CPCEquipedItemIV::Remove(short index, short count)
{
	return (this->*_Remove)(index, count);

	//TODO
}


hook_method<short (CPCEquipedItemIV::*)(unsigned long type)> CPCEquipedItemIV::_GetPlusPowerOfItem(SERVER, "CPCEquipedItemIV::GetPlusPowerOfItem");
short CPCEquipedItemIV::GetPlusPowerOfItem(unsigned long type)
{
	return (this->*_GetPlusPowerOfItem)(type);

	switch( type )
	{
	case VAR_PLUSATTACKPOWEROFITEM_RHAND     : return m_plusPowerOfItem.rightAttackPower;
	case VAR_PLUSATTACKPOWEROFITEM_LHAND     : return m_plusPowerOfItem.leftAttackPower;
	case VAR_PLUSDEFPOWEROFITEM              : return m_plusPowerOfItem.defencePower;
	case VAR_PLUSMDEFPOWEROFITEM             : return m_plusPowerOfItem.magicDefPower;
	case VAR_PLUSARROWPOWEROFITEM            : return m_plusPowerOfItem.equipedArrowAttPow;
	case VAR_PLUSATTREFININGPOWEROFITEM_RHAND: return m_plusPowerOfItem.rightrefiningAttPower;
	case VAR_PLUSATTREFININGPOWEROFITEM_LHAND: return m_plusPowerOfItem.leftrefiningAttPower;
	case VAR_PLUSDEFREFININGPOWEROFITEM      : return m_plusPowerOfItem.refiningDefPower;
	case VAR_PLUSMAGICPOWEROFITEM            : return m_plusPowerOfItem.magicAttackPower;
	default                                  : return 0;
	}
}


hook_method<int (CPCEquipedItemIV::*)(unsigned short& loc, IVItItem* item)> CPCEquipedItemIV::_IsEquipable(SERVER, "CPCEquipedItemIV::IsEquipable");
int CPCEquipedItemIV::IsEquipable(unsigned short& loc, IVItItem* item)
{
	return (this->*_IsEquipable)(loc, item);

	//TODO
}


IVItItem* CPCEquipedItemIV::GetEquipedArrow()
{
	return m_arrow;
}
