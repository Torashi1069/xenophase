#pragma once
#include "std/map"
#include "std/string"


class CMercenaryConfiguration
{
public:
	/* this+0x0 */ //const CMercenaryConfiguration::`vftable'
	/* static   */ private: static hook_ptr<CMercenaryConfiguration *> m_cpSelf;
	/* this+0x4 */ private: const char* m_ConfigurationFileName;
	/* this+0x8 */ private: bool m_bOK;
	/* this+0xC */ private: mystd::map<int,mystd::string> m_ScrollContainer;

	private: bool CMercenaryConfiguration::Create(void);
	public: bool CMercenaryConfiguration::isOK(void);
	public: bool CMercenaryConfiguration::isScroll(int in_ITID);
	public: static bool __cdecl CMercenaryConfiguration::CreateInstance(void);
	public: static void __cdecl CMercenaryConfiguration::DestroyInstance(void);
	private: CMercenaryConfiguration::CMercenaryConfiguration(void);
	private: virtual CMercenaryConfiguration::~CMercenaryConfiguration(void);

private:
	static hook_method<bool (CMercenaryConfiguration::*)(void)> CMercenaryConfiguration::_Create;
	static hook_method<bool (CMercenaryConfiguration::*)(void)> CMercenaryConfiguration::_isOK;
	static hook_method<bool (CMercenaryConfiguration::*)(int in_ITID)> CMercenaryConfiguration::_isScroll;
	static hook_method<static bool (__cdecl *)(void)> CMercenaryConfiguration::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CMercenaryConfiguration::_DestroyInstance;
};
