#pragma once
#include "std/map"
#include "std/string"


class CDBScriptInfo
{
public:
	/* this+0x0 */ //const CDBScriptInfo::`vftable'
	/* this+0x4 */ protected: mystd::map<mystd::string,mystd::string> m_map;

	public: CDBScriptInfo::CDBScriptInfo(void);
	public: virtual CDBScriptInfo::~CDBScriptInfo(void);
	public: int CDBScriptInfo::Load(const char* fileName);
	public: const char* CDBScriptInfo::Search(const char* type);

private:
	static hook_method<int (CDBScriptInfo::*)(const char* fileName)> CDBScriptInfo::_Load;
	static hook_method<const char* (CDBScriptInfo::*)(const char* type)> CDBScriptInfo::_Search;
};
