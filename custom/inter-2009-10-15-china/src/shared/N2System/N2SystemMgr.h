#pragma once


class N2SystemMgr
{
	/* this+0x0 */ void* vtable;
	/* static   */ private: static hook_ptr<N2SystemMgr*> m_cpSelf;
	/* this+0x4 */ private: bool m_bOK;

	//private: bool N2SystemMgr::Create();
	//private: void N2SystemMgr::Destory();
	//public: const bool N2SystemMgr::isOK();
	public: static bool __cdecl N2SystemMgr::CreateInstance(void);
	public: static void __cdecl N2SystemMgr::DestroyInstance(void);
	//private: void N2SystemMgr::N2SystemMgr();
	//private: void N2SystemMgr::~N2SystemMgr();

private:
	static hook_method<static bool (__cdecl *)(void)> N2SystemMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> N2SystemMgr::_DestroyInstance;
};
