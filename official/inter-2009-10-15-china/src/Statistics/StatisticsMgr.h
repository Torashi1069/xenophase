#pragma once
#include "CDateTime.h"


class CStatisticsMgr
{
	struct vtable_t
	{
		void* (CStatisticsMgr::* scalar_deleting_destructor)(unsigned int);
	};

	/* this+0x0 */ //const CStatisticsMgr::`vftable'
	/* static   */ private: static hook_ptr<CStatisticsMgr*> m_cpSelf;
	/* this+0x4 */ private: bool m_bOK;
	/* this+0x8 */ private: CDateTime m_LogOutputEvnetDT;
	/* this+0xC */ private: int m_ReportPerMinute;

	private: bool CStatisticsMgr::Create(void);
	private: void CStatisticsMgr::Destroy(void);
	public: bool CStatisticsMgr::isOK(void);
	public: void CStatisticsMgr::Process(void);
	public: static bool CStatisticsMgr::CreateInstance(void);
	public: static void CStatisticsMgr::DestroyInstance(void);
	public: static CStatisticsMgr* CStatisticsMgr::GetObj(void);
	private: CStatisticsMgr::CStatisticsMgr(void);
	private: virtual CStatisticsMgr::~CStatisticsMgr(void);

private:
	static hook_method<bool (CStatisticsMgr::*)(void)> CStatisticsMgr::_Create;
	static hook_method<void (CStatisticsMgr::*)(void)> CStatisticsMgr::_Destroy;
	static hook_method<bool (CStatisticsMgr::*)(void)> CStatisticsMgr::_isOK;
	static hook_method<void (CStatisticsMgr::*)(void)> CStatisticsMgr::_Process;
	static hook_method<static bool (__cdecl *)(void)> CStatisticsMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CStatisticsMgr::_DestroyInstance;
};
