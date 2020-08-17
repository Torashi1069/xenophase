#include "DBScriptInfo.h"


CDBScriptInfo::CDBScriptInfo(void)
{
}


CDBScriptInfo::~CDBScriptInfo(void)
{
}


hook_method<int (CDBScriptInfo::*)(const char* fileName)> CDBScriptInfo::_Load(SERVER, "CDBScriptInfo::Load");
int CDBScriptInfo::Load(const char* fileName)
{
	return (this->*_Load)(fileName);

	//TODO
}


hook_method<const char* (CDBScriptInfo::*)(const char* type)> CDBScriptInfo::_Search(SERVER, "CDBScriptInfo::Search");
const char* CDBScriptInfo::Search(const char* type)
{
	return (this->*_Search)(type);

	//TODO
}
