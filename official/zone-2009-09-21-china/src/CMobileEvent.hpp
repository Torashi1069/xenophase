#pragma once
#include "std/vector"
#include "struct.hpp"


class CMobileEvent
{
public:
	/* this+0x0  */ //const CMobileEvent::`vftable'
	/* this+0x4  */ mystd::vector<_MEventItemInfo> m_zenyList;
	/* this+0x14 */ mystd::vector<_MEventItemInfo> m_itemList;
	/* this+0x24 */ mystd::vector<_MEventItemInfo> m_couponList;
	/* this+0x34 */ bool m_isLoaded;
	/* this+0x38 */ int m_GID;
	/* this+0x3C */ int m_AID;

	public: CMobileEvent::CMobileEvent(void);
	public: virtual CMobileEvent::~CMobileEvent(void);
	public: void CMobileEvent::Init(int AID, int GID);
	public: bool CMobileEvent::GetMEventZeny(int index, int& zeny);
	public: bool CMobileEvent::GetMEventItem(int index, int& itemID, short& itemCount);
	public: bool CMobileEvent::GetMEventCoupon(int index, mystd::string& coupon);
	public: void CMobileEvent::GetMEventZenyName(int index, mystd::string& str);
	public: void CMobileEvent::GetMEventItemName(int index, mystd::string& str);
	public: void CMobileEvent::GetMEventItemID(int index, int& nItemID);
	public: void CMobileEvent::GetMEventCouponName(int index, mystd::string& str);
	public: bool CMobileEvent::Load(int aid);
	public: bool CMobileEvent::DeleteMEventZeny(int index);
	public: bool CMobileEvent::DeleteMEventItem(int index);
	public: bool CMobileEvent::DeleteMEventCoupon(int index);
	public: bool CMobileEvent::GetIsLoad(void);
	public: bool CMobileEvent::ReLoad(int aid);
	public: int CMobileEvent::CheckExpireTime(unsigned short year, unsigned short month, unsigned short day);

private:
	static hook_method<bool (CMobileEvent::*)(int index, int& zeny)> CMobileEvent::_GetMEventZeny;
	static hook_method<bool (CMobileEvent::*)(int index, int& itemID, short& itemCount)> CMobileEvent::_GetMEventItem;
	static hook_method<bool (CMobileEvent::*)(int index, mystd::string& coupon)> CMobileEvent::_GetMEventCoupon;
	static hook_method<void (CMobileEvent::*)(int index, mystd::string& str)> CMobileEvent::_GetMEventZenyName;
	static hook_method<void (CMobileEvent::*)(int index, mystd::string& str)> CMobileEvent::_GetMEventItemName;
	static hook_method<void (CMobileEvent::*)(int index, int& nItemID)> CMobileEvent::_GetMEventItemID;
	static hook_method<void (CMobileEvent::*)(int index, mystd::string& str)> CMobileEvent::_GetMEventCouponName;
	static hook_method<bool (CMobileEvent::*)(int aid)> CMobileEvent::_Load;
	static hook_method<bool (CMobileEvent::*)(int index)> CMobileEvent::_DeleteMEventZeny;
	static hook_method<bool (CMobileEvent::*)(int index)> CMobileEvent::_DeleteMEventItem;
	static hook_method<bool (CMobileEvent::*)(int index)> CMobileEvent::_DeleteMEventCoupon;
	static hook_method<bool (CMobileEvent::*)(void)> CMobileEvent::_GetIsLoad;
	static hook_method<bool (CMobileEvent::*)(int aid)> CMobileEvent::_ReLoad;
	static hook_method<int (CMobileEvent::*)(unsigned short year, unsigned short month, unsigned short day)> CMobileEvent::_CheckExpireTime;
};
