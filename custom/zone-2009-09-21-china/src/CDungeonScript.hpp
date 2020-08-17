#pragma once
#include "std/map"
#include "std/string"
class CList;


class CDungeonScript
{
public:
	/* this+0x0 */ //const CDungeonScript::`vftable'
	/* this+0x4 */ protected: mystd::map<mystd::string,CList *> m_map;

	public: CDungeonScript::CDungeonScript(void);
	public: virtual CDungeonScript::~CDungeonScript(void);
	public: bool CDungeonScript::Insert(const char* instantName);
	public: bool CDungeonScript::AddScript(const char* mapName, const char* FileName);
	public: const char* CDungeonScript::GetDungeonName(void);
	public: bool CDungeonScript::GetList(const char* name, mystd::list<mystd::string>& scriptList);
	public: void CDungeonScript::GetNext(void);
	public: int CDungeonScript::GetCount(void);

private:
	static hook_method<bool (CDungeonScript::*)(const char* instantName)> CDungeonScript::_Insert;
	static hook_method<bool (CDungeonScript::*)(const char* mapName, const char* FileName)> CDungeonScript::_AddScript;
	static hook_method<const char* (CDungeonScript::*)(void)> CDungeonScript::_GetDungeonName;
	static hook_method<bool (CDungeonScript::*)(const char* name, mystd::list<mystd::string>& scriptList)> CDungeonScript::_GetList;
	static hook_method<void (CDungeonScript::*)(void)> CDungeonScript::_GetNext;
	static hook_method<int (CDungeonScript::*)(void)> CDungeonScript::_GetCount;
};
