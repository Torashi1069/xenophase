#pragma once
#include "std/string"


struct TokenInfo
{
	/* this+0 */ long num;
	/* this+4 */ unsigned long type;
	/* this+8 */ mystd::string str;

	//public: void TokenInfo::Set(char, long, char *);
	//public: char* TokenInfo::GetStr();
	//public: void TokenInfo::TokenInfo();
	//public: void TokenInfo::~TokenInfo();
};


class CTokenMap
{
	/* this+0 */ private: mystd::map<mystd::string,TokenInfo> m_tokenMap;

	//public: CTokenMap::CTokenMap(void);
	//public: CTokenMap::~CTokenMap(void);
	//public: void CTokenMap::Set(const char *, struct TokenInfo &);
	public: void CTokenMap::Set(const char* name, int type, int num, char* str);
	//public: bool CTokenMap::Get(const char *, struct TokenInfo * &);

private:
	static hook_method<void (CTokenMap::*)(const char* name, int type, int num, char* str)> CTokenMap::_Set;
};
