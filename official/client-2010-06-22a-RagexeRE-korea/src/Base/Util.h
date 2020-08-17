#pragma once
#include "std/map"
#include "std/string"


void __cdecl MakeStringLower(mystd::string& s);


struct POINTER_FUNC
{
	int excuteType;
	void (__cdecl* pfunc)();
	int startTime;

	enum enumConfig
	{
		EXCUTE_ONCE   = 0,
		EXCUTE_REPEAT = 1,
		EXCUTE_RANDOM = 2,
	};
};


class CScheduler
{
	/* this+0 */ private: std::multimap<long,POINTER_FUNC> m_scheduleList;

	public: CScheduler::CScheduler(void);
	public: CScheduler::~CScheduler(void);
	public: void CScheduler::Clear(void);
	public: void CScheduler::OnRun(void);
	public: bool CScheduler::InsertInList(long excuteTime, int excuteType, void (__cdecl* pfunc)());
	public: bool CScheduler::InsertInList(long excuteTime, POINTER_FUNC pfunc);
	public: static CScheduler* __cdecl CScheduler::getInstance(void);

public:
	static hook_func<CScheduler (CScheduler::*)(void)> CScheduler::_cCScheduler;
	static hook_func<void (CScheduler::*)(void)> CScheduler::_dCScheduler;
	static hook_func<void (CScheduler::*)(void)> CScheduler::_Clear;
	static hook_func<void (CScheduler::*)(void)> CScheduler::_OnRun;
	static hook_func<bool (CScheduler::*)(long excuteTime, int excuteType, void (__cdecl* pfunc)())> CScheduler::_InsertInList;
	static hook_func<bool (CScheduler::*)(long excuteTime, POINTER_FUNC pfunc)> CScheduler::_InsertInList2;
	static hook_func<CScheduler* (__cdecl *)(void)> CScheduler::_getInstance;
};
