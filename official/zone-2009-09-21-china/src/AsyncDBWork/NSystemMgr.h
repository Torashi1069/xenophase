#pragma once


class NSystemMgr
{
	/* this+0x0 */ //const NSystemMgr::`vftable'
	/* static   */ private: static hook_ptr<NSystemMgr *> m_cpSelf;
	/* this+0x4 */ private: bool m_bOK;

	private: bool NSystemMgr::Create(void);
	private: void NSystemMgr::Destroy(void);
	//public: const bool NSystemMgr::isOK();
	//public: static NSystemMgr* NSystemMgr::GetObj();
	public: static bool __cdecl NSystemMgr::CreateInstance(void);
	public: static void __cdecl NSystemMgr::DestroyInstance(void);
	private: NSystemMgr::NSystemMgr(void);
	private: virtual NSystemMgr::~NSystemMgr(void);

private:
	static hook_method<bool (NSystemMgr::*)(void)> NSystemMgr::_Create;
	static hook_method<void (NSystemMgr::*)(void)> NSystemMgr::_Destroy;
	static hook_method<static bool (__cdecl *)(void)> NSystemMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> NSystemMgr::_DestroyInstance;
};
