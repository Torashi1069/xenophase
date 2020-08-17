#pragma once
#include "Instant Map/InstantMap.h"
#include "std/map"
#include "std/string"


class CInstantMapMgr
{
	/* this+0x0  */ void* vtable;
	/* this+0x4  */ private: bool m_bOK;
	/* static    */ private: static hook_ptr<CInstantMapMgr*> m_cpSelf;
	/* this+0x8  */ private: mystd::map<unsigned int,CInstantMap*> m_Container;
	/* this+0x14 */ private: mystd::map<mystd::string,unsigned int> m_IndexMap;

	typedef mystd::map<unsigned int,CInstantMap*>::const_iterator CONTAINER_ITER;
	typedef mystd::map<mystd::string,unsigned int>::const_iterator INDEXMAP_ITER;

	//private: bool CInstantMapMgr::Create();
	//private: void CInstantMapMgr::Destroy();
	//public: const bool CInstantMapMgr::isOK();
	public: void CInstantMapMgr::Process(void);
	public: const int CInstantMapMgr::GetNum(void);
	//public: bool CInstantMapMgr::InstantMapCreate(const unsigned int, const int, const mystd::string, const int);
	//public: bool CInstantMapMgr::InstantMapDestory(const unsigned int, const mystd::string);
	//public: mystd::string CInstantMapMgr::GetInstantMapName(const unsigned int);
	//public: void CInstantMapMgr::NotifyAllInstantMap(const int, const unsigned long &);
	public: static bool CInstantMapMgr::CreateInstance(void);
	public: static void CInstantMapMgr::DestroyInstance(void);
	public: static CInstantMapMgr* CInstantMapMgr::GetObj(void);
	//private: void CInstantMapMgr::CInstantMapMgr();
	//private: void CInstantMapMgr::~CInstantMapMgr();

private:
	static hook_method<void (CInstantMapMgr::*)(void)> CInstantMapMgr::_Process;
	static hook_method<const int (CInstantMapMgr::*)(void)> CInstantMapMgr::_GetNum;
	static hook_method<static bool (__cdecl *)(void)> CInstantMapMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CInstantMapMgr::_DestroyInstance;
};
