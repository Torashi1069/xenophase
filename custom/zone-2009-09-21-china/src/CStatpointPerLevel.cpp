#include "CStatpointPerLevel.hpp"


hook_ptr<const char *> CStatpointPerLevel::m_szpLoadFileName(SERVER, "CStatpointPerLevel::m_szpLoadFileName"); // = "statpointperlevel.scp";


CStatpointPerLevel::CStatpointPerLevel(void) // line 20
{
}


CStatpointPerLevel::~CStatpointPerLevel(void) // line 25
{
}


hook_method<void (CStatpointPerLevel::*)(void)> CStatpointPerLevel::_Init(SERVER, "CStatpointPerLevel::Init");
void CStatpointPerLevel::Init(void) // line 90
{
	return (this->*_Init)();

	//TODO
}


hook_method<int (CStatpointPerLevel::*)(void)> CStatpointPerLevel::_LoadStatpointPerLevel(SERVER, "CStatpointPerLevel::LoadStatpointPerLevel");
int CStatpointPerLevel::LoadStatpointPerLevel(void) // line 30
{
	return (this->*_LoadStatpointPerLevel)();

	//TODO
}


//hook_method<int (CStatpointPerLevel::*)(int nLevel)> CStatpointPerLevel::_GetStatpointPerLevel(SERVER, "CStatpointPerLevel::GetStatpointPerLevel");
int CStatpointPerLevel::GetStatpointPerLevel(int nLevel) // line ??
{
//	return (this->*_GetStatpointPerLevel)(nLevel);

	return m_statpointPerLevel[nLevel];
}
