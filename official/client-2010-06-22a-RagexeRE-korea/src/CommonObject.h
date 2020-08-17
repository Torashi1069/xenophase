#pragma once
#include "std/vector"


struct CommonObject
{
	/* this+0 */ mystd::vector<char*> m_deleteList;

	public: CommonObject::CommonObject(void);
	public: CommonObject::~CommonObject(void);
	public: void CommonObject::Clear(void);
	public: bool CommonObject::TokenFileToPCharList(mystd::vector<const char*>& pCharList, const char* fName, int type);

private:
	static hook_func<void (CommonObject::*)(void)> CommonObject::_Clear;
	static hook_func<bool (CommonObject::*)(mystd::vector<const char*>& pCharList, const char* fName, int type)> CommonObject::_TokenFileToPCharList;
};
