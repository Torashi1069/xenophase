#pragma once
#include "DBScriptInfo.h"


class ISDatabaseAccountMgr
{
	enum
	{
		MAXBYTES_DBPASSWORD = 256
	};

	/* this+0x0  */ void* vtable;
	/* static    */ private: static hook_ptr<ISDatabaseAccountMgr*> m_cpSelf;
	/* this+0x4  */ private: bool m_bOK;
	/* this+0x8  */ private: CDBScriptInfo m_DBScriptInfo;
	/* this+0x18 */ private: char m_DBpassword[MAXBYTES_DBPASSWORD+1];

	//private: bool ISDatabaseAccountMgr::Create();
	//private: void ISDatabaseAccountMgr::Destroy();
	//public: bool ISDatabaseAccountMgr::isOK();
	//public: class std::basic_string<char,std::char_traits<char>,std::allocator<char> > ISDatabaseAccountMgr::GetODBCConnectString(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >, const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
	public: static bool __cdecl ISDatabaseAccountMgr::CreateInstance(void);
	public: static void __cdecl ISDatabaseAccountMgr::DestroyInstance(void);
	//private: void ISDatabaseAccountMgr::ISDatabaseAccountMgr();
	//private: void ISDatabaseAccountMgr::~ISDatabaseAccountMgr();

private:
	static hook_method<static bool (__cdecl *)(void)> ISDatabaseAccountMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> ISDatabaseAccountMgr::_DestroyInstance;
};
