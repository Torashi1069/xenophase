#pragma once
#include "std/map"
#include "std/string"
class CDGNpcBin;


class CDGNpcMgr
{
public:
	/* this+0x0 */ //const CDGNpcMgr::`vftable'
	/* static   */ private: static hook_ptr<CDGNpcMgr*> m_cpSelf;
	/* this+0x4 */ protected: mystd::map<mystd::string, CDGNpcBin*> m_map;

	public: CDGNpcMgr::CDGNpcMgr(void);
	public: virtual CDGNpcMgr::~CDGNpcMgr(void);
	public: void CDGNpcMgr::Clear(void);
	public: static CDGNpcMgr* __cdecl CDGNpcMgr::GetObj(void);
	public: bool CDGNpcMgr::AddInstantMap(const char* mapName);
	public: void CDGNpcMgr::DeleteDunGeon(const char* mapName);
	public: CDGNpcBin* CDGNpcMgr::FindDunGeonBin(const char* mapName);

private:
	static hook_method<void (CDGNpcMgr::*)(void)> CDGNpcMgr::_Clear;
	static hook_method<static CDGNpcMgr* (__cdecl *)(void)> CDGNpcMgr::_GetObj;
	static hook_method<bool (CDGNpcMgr::*)(const char* mapName)> CDGNpcMgr::_AddInstantMap;
	static hook_method<void (CDGNpcMgr::*)(const char* mapName)> CDGNpcMgr::_DeleteDunGeon;
	static hook_method<CDGNpcBin* (CDGNpcMgr::*)(const char* mapName)> CDGNpcMgr::_FindDunGeonBin;
};
