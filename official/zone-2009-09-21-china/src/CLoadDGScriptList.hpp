#pragma once
#include "std/list"
#include "std/string"
#include "CDungeonScript.hpp"


class CLoadDGScriptList
{
	/* this+0x0 */ public: //const CLoadDGScriptList::`vftable';
	/* this+0x4 */ private: char* m_buff;
	/* this+0x8 */ private: int m_tSize;
	/* this+0xC */ private: CDungeonScript m_list;

	public: CLoadDGScriptList::CLoadDGScriptList(void);
	public: virtual CLoadDGScriptList::~CLoadDGScriptList(void);
	public: bool CLoadDGScriptList::Load(const char* filename);
	//public: bool CLoadDGScriptList::CuttingNote(void);
	public: bool CLoadDGScriptList::Parsing(void);
	public: int CLoadDGScriptList::GetListCount(void);
	public: const char* CLoadDGScriptList::GetList(mystd::list<mystd::string>& scList);
	public: void CLoadDGScriptList::GetNext(void);

private:
	static hook_method<bool (CLoadDGScriptList::*)(const char* filename)> CLoadDGScriptList::_Load;
	static hook_method<bool (CLoadDGScriptList::*)(void)> CLoadDGScriptList::_Parsing;
	static hook_method<int (CLoadDGScriptList::*)(void)> CLoadDGScriptList::_GetListCount;
	static hook_method<const char* (CLoadDGScriptList::*)(mystd::list<mystd::string>& scList)> CLoadDGScriptList::_GetList;
	static hook_method<void (CLoadDGScriptList::*)(void)> CLoadDGScriptList::_GetNext;
};
