#include "CLoadDGScriptList.hpp"


CLoadDGScriptList::CLoadDGScriptList(void) // line 130
{
	m_buff = NULL;
	m_tSize = 0;
}


CLoadDGScriptList::~CLoadDGScriptList(void) // line 136
{
	if( m_buff != NULL )
	{
		delete[] m_buff;
		m_buff = NULL;
	}
	m_tSize = 0;
}


hook_method<bool (CLoadDGScriptList::*)(const char* filename)> CLoadDGScriptList::_Load(SERVER, "CLoadDGScriptList::Load");
bool CLoadDGScriptList::Load(const char* filename) // line 146
{
	return (this->*_Load)(filename);

	//TODO
}


hook_method<bool (CLoadDGScriptList::*)(void)> CLoadDGScriptList::_Parsing(SERVER, "CLoadDGScriptList::Parsing");
bool CLoadDGScriptList::Parsing(void) // line 169
{
	return (this->*_Parsing)();

	//TODO
}


//hook_method<int (CLoadDGScriptList::*)(void)> CLoadDGScriptList::_GetListCount(SERVER, "CLoadDGScriptList::GetListCount");
int CLoadDGScriptList::GetListCount(void) // line ???
{
//	return (this->*_GetListCount))();

	return m_list.GetCount();
}


hook_method<const char* (CLoadDGScriptList::*)(mystd::list<mystd::string>& scList)> CLoadDGScriptList::_GetList(SERVER, "CLoadDGScriptList::GetList");
const char* CLoadDGScriptList::GetList(mystd::list<mystd::string>& scList) // line 249
{
	return (this->*_GetList)(scList);

	//TODO
}


hook_method<void (CLoadDGScriptList::*)(void)> CLoadDGScriptList::_GetNext(SERVER, "CLoadDGScriptList::GetNext");
void CLoadDGScriptList::GetNext(void) // line 257
{
	return (this->*_GetNext)();

	//TODO
}
