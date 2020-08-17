#pragma once
#include "std/map"


struct ITEMREUSE
{
	/* this+0 */ int groupBuffID;
	/* this+4 */ unsigned long time;

	public: ITEMREUSE::ITEMREUSE(void)
	{
		this->groupBuffID = -1;
		this->time = 0;
	}
};


class CItemReuseLimit
{
	/* this+0 */ private: mystd::map<unsigned long,ITEMREUSE> m_info;

	public: bool CItemReuseLimit::Init(void);
	public: bool CItemReuseLimit::GetItemReuseLimit(unsigned long itemID, ITEMREUSE& info);

private:
	static hook_method<bool (CItemReuseLimit::*)(void)> CItemReuseLimit::_Init;
	static hook_method<bool (CItemReuseLimit::*)(unsigned long itemID, ITEMREUSE& info)> CItemReuseLimit::_GetItemReuseLimit;
};
