#pragma once
#include "N2DBLogThread.h"
#include "std/vector"


class N2DBLogMgr
{
	/* this+ 0 */ public: //const N2DBLogMgr::`vftable';
	/* static  */ private: static hook_ptr<N2DBLogMgr*> m_cpSelf;
	/* this+ 4 */ private: bool m_bOK;
	/* this+ 8 */ private: mystd::vector<N2DBLogThread*> m_ThreadContainer;
	/* this+24 */ private: N2DBLogRequestQueue m_RequestQueue;

	private: bool N2DBLogMgr::Create(const int in_WorkThreadNum, const mystd::string in_ConnectStr);
	private: void N2DBLogMgr::Destroy(void);
	public: const bool N2DBLogMgr::isOK(void) const; // line 25
	public: bool N2DBLogMgr::Start(void);
	public: void N2DBLogMgr::Stop(void);
	public: bool N2DBLogMgr::Add(N2DBLog* const in_cpDBLog); // line 28
	public: static bool N2DBLogMgr::CreateInstance(const int in_WorkThreadNum, const mystd::string in_ConnectStr);
	public: static void N2DBLogMgr::DestroyInstance(void);
	private: N2DBLogMgr::N2DBLogMgr(const int in_WorkThreadNum, const mystd::string in_ConnectStr);
	private: virtual N2DBLogMgr::~N2DBLogMgr(void);
	friend N2DBLogMgr* __cdecl InstanceN2DBLogMgr(void);

private:
	static hook_method<bool (N2DBLogMgr::*)(const int in_WorkThreadNum, const mystd::string in_ConnectStr)> N2DBLogMgr::_Create;
	static hook_method<void (N2DBLogMgr::*)(void)> N2DBLogMgr::_Destroy;
	static hook_method<const bool (N2DBLogMgr::*)(void) const> N2DBLogMgr::_isOK;
	static hook_method<bool (N2DBLogMgr::*)(void)> N2DBLogMgr::_Start;
	static hook_method<void (N2DBLogMgr::*)(void)> N2DBLogMgr::_Stop;
	static hook_method<bool (N2DBLogMgr::*)(N2DBLog* const in_cpDBLog)> N2DBLogMgr::_Add;
	static hook_method<static bool (__cdecl *)(const int in_WorkThreadNum, const mystd::string in_ConnectStr)> N2DBLogMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> N2DBLogMgr::_DestroyInstance;
};


N2DBLogMgr* __cdecl InstanceN2DBLogMgr(void); // line 39
