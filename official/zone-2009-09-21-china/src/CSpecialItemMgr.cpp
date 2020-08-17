#include "CSpecialItemMgr.hpp"


CSpecialItemMgr::CSpecialItemMgr(void)
{
}


CSpecialItemMgr::~CSpecialItemMgr(void)
{
}


hook_method<bool (CSpecialItemMgr::*)(void)> CSpecialItemMgr::_Init(SERVER, "CSpecialItemMgr::Init");
bool CSpecialItemMgr::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CSpecialItemMgr::*)(unsigned long ITID, unsigned long EventID, unsigned long senderAID)> CSpecialItemMgr::_SendMsg(SERVER, "CSpecialItemMgr::SendMsg");
void CSpecialItemMgr::SendMsg(unsigned long ITID, unsigned long EventID, unsigned long senderAID)
{
	return (this->*_SendMsg)(ITID, EventID, senderAID);

	//TODO
}
