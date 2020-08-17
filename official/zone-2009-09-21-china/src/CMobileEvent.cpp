#include "CMobileEvent.hpp"


CMobileEvent::CMobileEvent(void)
{
}


CMobileEvent::~CMobileEvent(void)
{
}


hook_method<bool (CMobileEvent::*)(int index, int& zeny)> CMobileEvent::_GetMEventZeny(SERVER, "CMobileEvent::GetMEventZeny");
bool CMobileEvent::GetMEventZeny(int index, int& zeny)
{
	return (this->*_GetMEventZeny)(index, zeny);

	//TODO
}


hook_method<bool (CMobileEvent::*)(int index, int& itemID, short& itemCount)> CMobileEvent::_GetMEventItem(SERVER, "CMobileEvent::GetMEventItem");
bool CMobileEvent::GetMEventItem(int index, int& itemID, short& itemCount)
{
	return (this->*_GetMEventItem)(index, itemID, itemCount);

	//TODO
}


/* hook_method<bool (CMobileEvent::*)(int index, mystd::string& coupon)> CMobileEvent::_GetMEventCoupon(SERVER, "CMobileEvent::GetMEventCoupon");
bool CMobileEvent::GetMEventCoupon(int index, mystd::string& coupon)
{
	return (this->*_GetMEventCoupon)(index, coupon);

	//TODO
} */

hook_method<void (CMobileEvent::*)(int index, mystd::string& str)> CMobileEvent::_GetMEventZenyName(SERVER, "CMobileEvent::GetMEventZenyName");
void CMobileEvent::GetMEventZenyName(int index, mystd::string& str)
{
	return (this->*_GetMEventZenyName)(index, str);

	//TODO
}


hook_method<void (CMobileEvent::*)(int index, mystd::string& str)> CMobileEvent::_GetMEventItemName(SERVER, "CMobileEvent::GetMEventItemName");
void CMobileEvent::GetMEventItemName(int index, mystd::string& str)
{
	return (this->*_GetMEventItemName)(index, str);

	//TODO
}


hook_method<void (CMobileEvent::*)(int index, int& nItemID)> CMobileEvent::_GetMEventItemID(SERVER, "CMobileEvent::GetMEventItemID");
void CMobileEvent::GetMEventItemID(int index, int& nItemID)
{
	return (this->*_GetMEventItemID)(index, nItemID);

	//TODO
}


/* hook_method<void (CMobileEvent::*)(int index, mystd::string& str)> CMobileEvent::_GetMEventCouponName(SERVER, "CMobileEvent::GetMEventCouponName");
void CMobileEvent::GetMEventCouponName(int index, mystd::string& str)
{
	return (this->*_GetMEventCouponName)(index, str);

	//TODO
} */


hook_method<bool (CMobileEvent::*)(int aid)> CMobileEvent::_Load(SERVER, "CMobileEvent::Load");
bool CMobileEvent::Load(int aid)
{
	return (this->*_Load)(aid);

	//TODO
}


hook_method<bool (CMobileEvent::*)(int index)> CMobileEvent::_DeleteMEventZeny(SERVER, "CMobileEvent::DeleteMEventZeny");
bool CMobileEvent::DeleteMEventZeny(int index)
{
	return (this->*_DeleteMEventZeny)(index);

	//TODO
}


hook_method<bool (CMobileEvent::*)(int index)> CMobileEvent::_DeleteMEventItem(SERVER, "CMobileEvent::DeleteMEventItem");
bool CMobileEvent::DeleteMEventItem(int index)
{
	return (this->*_DeleteMEventItem)(index);

	//TODO
}


/* hook_method<bool (CMobileEvent::*)(int index)> CMobileEvent::_DeleteMEventCoupon(SERVER, "CMobileEvent::DeleteMEventCoupon");
bool CMobileEvent::DeleteMEventCoupon(int index)
{
	return (this->*_DeleteMEventCoupon)(index);

	//TODO
} */


//hook_method<bool (CMobileEvent::*)(void)> CMobileEvent::_GetIsLoad(SERVER, "CMobileEvent::GetIsLoad");
bool CMobileEvent::GetIsLoad(void)
{
//	return (this->*_GetIsLoad)();

	return m_isLoaded;
}


hook_method<bool (CMobileEvent::*)(int aid)> CMobileEvent::_ReLoad(SERVER, "CMobileEvent::ReLoad");
bool CMobileEvent::ReLoad(int aid)
{
	return (this->*_ReLoad)(aid);

	//TODO
}


hook_method<int (CMobileEvent::*)(unsigned short year, unsigned short month, unsigned short day)> CMobileEvent::_CheckExpireTime(SERVER, "CMobileEvent::CheckExpireTime");
int CMobileEvent::CheckExpireTime(unsigned short year, unsigned short month, unsigned short day)
{
	return (this->*_CheckExpireTime)(year, month, day);

	//TODO
}

