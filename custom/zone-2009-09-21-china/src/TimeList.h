#pragma once
#include "std/map"


class CTimeList
{
	/* this+0 */ public: //const CTimeList::`vftable';
	/* this+4 */ private: mystd::map<int,time_t> m_index2Time;

	enum { MAX_TIMELIST_SIZE = 50 };

	public: CTimeList::CTimeList(void);
	public: virtual CTimeList::~CTimeList(void);
	public: bool CTimeList::IsTimeListFull(void);
	public: time_t CTimeList::FindTimeList(int ti);
	public: int CTimeList::AddTimeList(int ti);
	//public: bool CTimeList::DeleteTimeList(int);
	public: bool CTimeList::SetTimeList(int ti, int delta);
	//public: void CTimeList::ClearTimeList(void);
	//public: int CTimeList::ReadBinary(unsigned char *, int);
	public: int CTimeList::WriteBinary(unsigned char* buf, int& len);
	public: void CTimeList::DisplayTimeList(mystd::string& str);

private:
	static hook_method<bool (CTimeList::*)(void)> CTimeList::_IsTimeListFull;
	static hook_method<time_t (CTimeList::*)(int ti)> CTimeList::_FindTimeList;
	static hook_method<int (CTimeList::*)(int ti)> CTimeList::_AddTimeList;
	static hook_method<bool (CTimeList::*)(int ti, int delta)> CTimeList::_SetTimeList;
	static hook_method<int (CTimeList::*)(unsigned char* buf, int& len)> CTimeList::_WriteBinary;
	static hook_method<void (CTimeList::*)(mystd::string& str)> CTimeList::_DisplayTimeList;
};
