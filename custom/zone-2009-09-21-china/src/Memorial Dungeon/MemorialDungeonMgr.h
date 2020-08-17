#pragma once
#include "std/map"
#include "Memorial Dungeon/MemorialDungeon.h"


class CMemorialDungeonMgr
{
public:
	enum enumOpenState
	{
		OPENSTATE_UNKNOWN = 0x0,
		OPENSTATE_OPEN    = 0x1,
		OPENSTATE_CLOSE   = 0x2,
	};

	/* this+0x0  */ //const CMemorialDungeonMgr::`vftable'
	/* static    */ private: static hook_ptr<CMemorialDungeonMgr *> m_cpSelf;
	/* this+0x4  */ private: bool m_bOK;
	/* this+0x8  */ private: mystd::map<unsigned long,CMemorialDungeon> m_Container;
	/* this+0x14 */ private: enum CMemorialDungeonMgr::enumOpenState m_OpenState;

	private: bool CMemorialDungeonMgr::Create(void);
	private: void CMemorialDungeonMgr::Destroy(void);
	//public: bool CMemorialDungeonMgr::isOK();
	//public: void CMemorialDungeonMgr::Add(const unsigned long, const mystd::string, const unsigned long, const mystd::string, const unsigned long, const int);
	//public: void CMemorialDungeonMgr::Remove(const unsigned long);
	//public: bool CMemorialDungeonMgr::Exist(const unsigned long, const mystd::string);
	//public: void CMemorialDungeonMgr::DisconnectISVR();
	//public: enum CMemorialDungeonMgr::enumOpenState GetOpenState();
	//public: void CMemorialDungeonMgr::SetOpenState(enum CMemorialDungeonMgr::enumOpenState);
	public: static bool __cdecl CMemorialDungeonMgr::CreateInstance(void);
	public: static void __cdecl CMemorialDungeonMgr::DestroyInstance(void);
	private: CMemorialDungeonMgr::CMemorialDungeonMgr(void);
	private: virtual CMemorialDungeonMgr::~CMemorialDungeonMgr(void);

private:
	static hook_method<bool (CMemorialDungeonMgr::*)(void)> CMemorialDungeonMgr::_Create;
	static hook_method<void (CMemorialDungeonMgr::*)(void)> CMemorialDungeonMgr::_Destroy;
	static hook_method<static bool (__cdecl *)(void)> CMemorialDungeonMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CMemorialDungeonMgr::_DestroyInstance;
};
