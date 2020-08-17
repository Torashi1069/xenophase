#include "Memorial Dungeon/MemorialDungeonDBLog.h"
#include "N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"


class CMemorialDungeonDBLogMgr
{
	/* this+0 */ public: //const CMemorialDungeonDBLogMgr::`vftable';
	/* static */ private: static hook_ptr<CMemorialDungeonDBLogMgr*> m_cpSelf;
	/* this+4 */ private: bool m_bOK;
	/* this+8 */ private: N2ODBCCtrl m_ODBCCtrl;

	private: CMemorialDungeonDBLogMgr::CMemorialDungeonDBLogMgr(void);
	private: virtual CMemorialDungeonDBLogMgr::~CMemorialDungeonDBLogMgr(void);
	private: bool CMemorialDungeonDBLogMgr::Create(void);
	private: void CMemorialDungeonDBLogMgr::Destroy(void);
	public: bool CMemorialDungeonDBLogMgr::isOK(void) const; // line 22
	public: void CMemorialDungeonDBLogMgr::Add(const enum CMemorialDungeonDBLog::enumTYPE in_Type, const mystd::string in_MemorialDungeonName, const mystd::string in_PartyName, const int in_PartyID, const int in_ZSID);
	public: static bool __cdecl CMemorialDungeonDBLogMgr::CreateInstance(void);
	public: static void __cdecl CMemorialDungeonDBLogMgr::DestroyInstance(void);
	friend CMemorialDungeonDBLogMgr* __cdecl InstanceCMemorialDungeonDBLogMgr(void);

private:
	static hook_method<bool (CMemorialDungeonDBLogMgr::*)(void)> CMemorialDungeonDBLogMgr::_Create;
	static hook_method<void (CMemorialDungeonDBLogMgr::*)(void)> CMemorialDungeonDBLogMgr::_Destroy;
	static hook_method<bool (CMemorialDungeonDBLogMgr::*)(void) const> CMemorialDungeonDBLogMgr::_isOK;
	static hook_method<void (CMemorialDungeonDBLogMgr::*)(const enum CMemorialDungeonDBLog::enumTYPE in_Type, const mystd::string in_MemorialDungeonName, const mystd::string in_PartyName, const int in_PartyID, const int in_ZSID)> CMemorialDungeonDBLogMgr::_Add;
	static hook_method<static bool (__cdecl *)(void)> CMemorialDungeonDBLogMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CMemorialDungeonDBLogMgr::_DestroyInstance;
};


CMemorialDungeonDBLogMgr* __cdecl InstanceCMemorialDungeonDBLogMgr(void); // line 41
