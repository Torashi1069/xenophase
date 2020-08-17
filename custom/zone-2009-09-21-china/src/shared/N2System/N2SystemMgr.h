#pragma once


class N2SystemMgr
{
public:
	/* this+0x0 */ //const N2SystemMgr::`vftable'
	/* static   */ private: static hook_ptr<N2SystemMgr *> m_cpSelf;
	/* this+0x4 */ private: bool m_bOK;

	private: bool N2SystemMgr::Create(void);
	private: void N2SystemMgr::Destroy(void);
	public: const bool N2SystemMgr::isOK(void);
	public: static bool __cdecl N2SystemMgr::CreateInstance(void);
	public: static void __cdecl N2SystemMgr::DestroyInstance(void);
	private: N2SystemMgr::N2SystemMgr(void);
	private: virtual N2SystemMgr::~N2SystemMgr(void);

private:
	static hook_method<bool (N2SystemMgr::*)(void)> N2SystemMgr::_Create;
	static hook_method<void (N2SystemMgr::*)(void)> N2SystemMgr::_Destroy;
	static hook_method<const bool (N2SystemMgr::*)(void)> N2SystemMgr::_isOK;
	static hook_method<static bool (__cdecl *)(void)> N2SystemMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> N2SystemMgr::_DestroyInstance;
};
