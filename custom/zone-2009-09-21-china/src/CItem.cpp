#include "enum.hpp"
#include "CItem.hpp"


CItem::CItem(void)
{
	m_type = ITEM_TYPE;
	m_mapRes = NULL;
}


CItem::~CItem(void)
{
}


/* hook_method<const char* (CItem::*)(void)> CItem::_GetName(SERVER, "CItem::GetName");
const char* CItem::GetName(void)
{
	return (this->*_GetName)();

	//TODO
} */


//hook_method<unsigned long (CItem::*)(void)> CItem::_GetAccountID(SERVER, "CItem::GetAccountID");
unsigned long CItem::GetAccountID(void)
{
//	return (this->*_GetAccountID)();

	return m_ITAID;
}


hook_method<void (CItem::*)(CITP* itp, ITEM_INFO* itemInfo)> CItem::_Init(SERVER, "CItem::Init");
void CItem::Init(CITP* itp, ITEM_INFO* itemInfo)
{
	return (this->*_Init)(itp, itemInfo);

	//TODO
}


hook_method<void (CItem::*)(mystd::vector<CCharacter*>* section)> CItem::_UpdateItem(SERVER, "CItem::UpdateItem");
void CItem::UpdateItem(mystd::vector<CCharacter*>* section)
{
	return (this->*_UpdateItem)(section);

	//TODO
}


//hook_method<void (CItem::*)(void)> CItem::_Reset(SERVER, "CItem::Reset");
void CItem::Reset(void)
{
//	return (this->*_Reset)();

	m_itemInfo.xPos    = 0;
	m_itemInfo.yPos    = 0;
	m_itemInfo.subX    = 0;
	m_itemInfo.subY    = 0;
	m_itemInfo.mapRes  = 0;
	m_itemInfo.name[0] = '\0';
}


hook_method<int (CItem::*)(void)> CItem::_OnProcess(SERVER, "CItem::OnProcess");
int CItem::OnProcess(void)
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<void (CItem::*)(void)> CItem::_CheckStateChange(SERVER, "CItem::CheckStateChange");
void CItem::CheckStateChange(void)
{
	return (this->*_CheckStateChange)();

	//TODO
}


hook_method<void (CItem::*)(CPC* other)> CItem::_NotifyUpdateInfo(SERVER, "CItem::NotifyUpdateInfo");
void CItem::NotifyUpdateInfo(CPC* other)
{
	return (this->*_NotifyUpdateInfo)(other);

	//TODO
}


hook_method<void (CItem::*)(void)> CItem::_OnDisappear(SERVER, "CItem::OnDisappear");
void CItem::OnDisappear(void)
{
	return (this->*_OnDisappear)();

	//TODO
}


hook_method<int (CItem::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CItem::_OnMsg(SERVER, "CItem::OnMsg");
int CItem::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	//TODO
}


hook_method<int (CItem::*)(unsigned short id, int& value)> CItem::_GetParameterValue(SERVER, "CItem::GetParameterValue");
int CItem::GetParameterValue(unsigned short id, int& value)
{
	return (this->*_GetParameterValue)(id, value);

	//TODO
}


hook_method<int (CItem::*)(unsigned short id, int value)> CItem::_UpdateParameterValue(SERVER, "CItem::UpdateParameterValue");
int CItem::UpdateParameterValue(unsigned short id, int value)
{
	return (this->*_UpdateParameterValue)(id, value);

	//TODO
}


hook_method<void (CItem::*)(COMMAND_QUEUE* command)> CItem::_InsertCommand(SERVER, "CItem::InsertCommand");
void CItem::InsertCommand(COMMAND_QUEUE* command)
{
	return (this->*_InsertCommand)(command);

	//TODO
}


hook_method<void (CItem::*)(void)> CItem::_CheckCommandQueue(SERVER, "CItem::CheckCommandQueue");
void CItem::CheckCommandQueue(void)
{
	return (this->*_CheckCommandQueue)();

	//TODO
}


hook_method<void (CItem::*)(unsigned long commandID)> CItem::_DisableCommand(SERVER, "CItem::DisableCommand");
void CItem::DisableCommand(unsigned long commandID)
{
	return (this->*_DisableCommand)(commandID);

	//TODO
}


hook_method<int (CItem::*)(CCharacter* ch, int range)> CItem::_IsMyArea(SERVER, "CItem::IsMyArea");
int CItem::IsMyArea(CCharacter* ch, int range)
{
	return (this->*_IsMyArea)(ch, range);

	//TODO
}


hook_method<int (CItem::*)(CCharacter* ch, unsigned long flag)> CItem::_IsTarget(SERVER, "CItem::IsTarget");
int CItem::IsTarget(CCharacter* ch, unsigned long flag)
{
	return (this->*_IsTarget)(ch, flag);

	//TODO
}


//hook_method<void (CItem::*)(unsigned long ITAID)> CItem::_SetAccountID(SERVER, "CItem::SetAccountID");
void CItem::SetAccountID(unsigned long ITAID)
{
//	return (this->*_SetAccountID)(ITAID);

	m_ITAID = ITAID;
}


//hook_method<unsigned short (CItem::*)(void)> CItem::_GetITID(SERVER, "CItem::GetITID");
unsigned short CItem::GetITID(void)
{
//	return (this->*_GetITID)();

	return m_itemInfo.ITID;
}


//hook_method<unsigned short (CItem::*)(void)> CItem::_GetCount(SERVER, "CItem::GetCount");
unsigned short CItem::GetCount(void)
{
//	return (this->*_GetCount)();

	return m_itemInfo.count;
}


//hook_method<void (CItem::*)(unsigned long type)> CItem::_SetPickableType(SERVER, "CItem::SetPickableType");
void CItem::SetPickableType(unsigned long type)
{
//	return (this->*_SetPickableType)(type);

	m_pickableType = type;
}


//hook_method<unsigned long (CItem::*)(void)> CItem::_GetPickableType(SERVER, "CItem::GetPickableType");
unsigned long CItem::GetPickableType(void)
{
//	return (this->*_GetPickableType)();

	return m_pickableType;
}


//hook_method<void (CItem::*)(unsigned long PAID)> CItem::_SetPickableParty(SERVER, "CItem::SetPickableParty");
void CItem::SetPickableParty(unsigned long PAID)
{
//	return (this->*_SetPickableParty)(PAID);

	m_pickablePARTYID = PAID;
}


//hook_method<unsigned long (CItem::*)(void)> CItem::_GetPickablePartyID(SERVER, "CItem::GetPickablePartyID");
unsigned long CItem::GetPickablePartyID(void)
{
//	return (this->*_GetPickablePartyID)();

	return m_pickablePARTYID;
}


hook_method<void (CItem::*)(unsigned long val, unsigned long time)> CItem::_AddPickupablePC(SERVER, "CItem::AddPickupablePC");
void CItem::AddPickupablePC(unsigned long val, unsigned long time)
{
	return (this->*_AddPickupablePC)(val, time);

	//TODO
}


hook_method<int (CItem::*)(unsigned long val)> CItem::_IsPickUpable(SERVER, "CItem::IsPickUpable");
int CItem::IsPickUpable(unsigned long val)
{
	return (this->*_IsPickUpable)(val);

	//TODO
}


//hook_method<void (CItem::*)(const __int64 in_unigue_identity_number)> CItem::_SetUniqueIdentifyNumber(SERVER, "CItem::SetUniqueIdentifyNumber");
void CItem::SetUniqueIdentifyNumber(const __int64 in_unigue_identity_number)
{
//	return (this->*_SetUniqueIdentifyNumber)(in_unigue_identity_number);

	m_itemInfo.unique_identity_numberV2 = in_unigue_identity_number;
}


//hook_method<__int64 (CItem::*)(void)> CItem::_GetUniqueIdentityNumber(SERVER, "CItem::GetUniqueIdentityNumber");
__int64 CItem::GetUniqueIdentityNumber(void)
{
//	return (this->*_GetUniqueIdentityNumber)();

	return m_itemInfo.unique_identity_numberV2;
}


//hook_method<long (CItem::*)(void)> CItem::_GetHireExpireDate(SERVER, "CItem::GetHireExpireDate");
long CItem::GetHireExpireDate(void)
{
//	return (this->*_GetHireExpireDate)();

	return m_itemInfo.hire_expire_date;
}


//hook_method<void (CItem::*)(unsigned long time)> CItem::_SetPickableTime(SERVER, "CItem::SetPickableTime");
void CItem::SetPickableTime(unsigned long time)
{
//	return (this->*_SetPickableTime)(time);

	m_pickableTime = time;
}


//hook_method<void (CItem::*)(int par1)> CItem::_InitThePCCacheInfo(SERVER, "CItem::InitThePCCacheInfo");
void CItem::InitThePCCacheInfo(int par1)
{
//	return (this->*_InitThePCCacheInfo)(par1);

	m_neighborCache.CNeighborCache::InitThePCCacheInfo(par1);
}
