#include "DBScriptInfo.h"


CDBScriptInfo::CDBScriptInfo(void) // line 9
{
}


CDBScriptInfo::~CDBScriptInfo(void) // line 13
{
}


hook_method<int (CDBScriptInfo::*)(const char* fileName)> CDBScriptInfo::_Load(SERVER, "CDBScriptInfo::Load");
int CDBScriptInfo::Load(const char* fileName) // line 18
{
	return (this->*_Load)(fileName);

	//TODO
}


hook_method<const char* (CDBScriptInfo::*)(const char* type)> CDBScriptInfo::_Search(SERVER, "CDBScriptInfo::Search");
const char* CDBScriptInfo::Search(const char* type) // line 45
{
	return (this->*_Search)(type);

	//TODO
}
