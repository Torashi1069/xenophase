#include "PC.h"
#include "CPCProperty.hpp"


CPCProperty::CPCProperty(CPC* pc)
{
	m_pc = pc;
	this->CPCProperty::Reset();
}


hook_method<void (CPCProperty::*)(void)> CPCProperty::_Reset(SERVER, "CPCProperty::Reset");
void CPCProperty::Reset(void)
{
	return (this->*_Reset)();

	memset(&m_propertys, 0, sizeof(m_propertys));
}


hook_method<void (CPCProperty::*)(void)> CPCProperty::_UpdateNotifyItemDef(SERVER, "CPCProperty::UpdateNotifyItemDef");
void CPCProperty::UpdateNotifyItemDef(void)
{
	return (this->*_UpdateNotifyItemDef)();

	m_propertys.notifyItemDef = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSDEFPOWEROFITEM)
	                          + m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSDEFREFININGPOWEROFITEM)
	                          + m_pc->m_characterInfo.extItemDefPower;
}
