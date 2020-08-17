#pragma once
#include "std/map"
class CInstantMapCtrl;


class CInstantMapMgr
{
public:
	/* this+0x0  */ //const CInstantMapMgr::`vftable'
	/* this+0x4  */ private: mystd::map<unsigned int,CInstantMapCtrl *> m_InstantMapCtrlContainer;
	/* this+0x10 */ private: bool m_bOK;
	/* static    */ private: static hook_ptr<CInstantMapMgr *> m_cpSelf;

	typedef mystd::map<unsigned int,CInstantMapCtrl *>::const_iterator INSTANTMAPCTRL_CONTAINER_ITER;

	private: bool CInstantMapMgr::Create(void);
	private: void CInstantMapMgr::Destroy(void);
	//private: const bool CInstantMapMgr::isOK();
	//private: CInstantMapCtrl* CInstantMapMgr::GetInstantMapCtrlPtr(const mystd::string, const int);
	public: void CInstantMapMgr::Process(void);
	public: bool CInstantMapMgr::Start(void);
	public: void CInstantMapMgr::Stop(void);
	//public: bool CInstantMapMgr::RequestCreate(const unsigned int, const int, const mystd::string, const int);
	//public: void CInstantMapMgr::RequestDestory(const int, const mystd::string);
	public: int CInstantMapMgr::GetCtrlCount(void);
	//public: void CInstantMapMgr::SetPlayerEnter(const unsigned int, const int, const mystd::string, const int, const int, const bool);
	//public: void CInstantMapMgr::DisconnectISVR();
	public: static bool __cdecl CInstantMapMgr::CreateInstance(void);
	public: static void __cdecl CInstantMapMgr::DestroyInstance(void);
	public: static CInstantMapMgr* CInstantMapMgr::GetObj(void);
	private: CInstantMapMgr::CInstantMapMgr(void);
	private: virtual CInstantMapMgr::~CInstantMapMgr(void);

private:
	static hook_method<bool (CInstantMapMgr::*)(void)> CInstantMapMgr::_Create;
	static hook_method<void (CInstantMapMgr::*)(void)> CInstantMapMgr::_Destroy;
	static hook_method<void (CInstantMapMgr::*)(void)> CInstantMapMgr::_Process;
	static hook_method<bool (CInstantMapMgr::*)(void)> CInstantMapMgr::_Start;
	static hook_method<void (CInstantMapMgr::*)(void)> CInstantMapMgr::_Stop;
	static hook_method<int (CInstantMapMgr::*)(void)> CInstantMapMgr::_GetCtrlCount;
	static hook_method<static bool (__cdecl *)(void)> CInstantMapMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CInstantMapMgr::_DestroyInstance;
};
