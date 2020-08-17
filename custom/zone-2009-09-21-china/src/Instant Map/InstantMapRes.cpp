#include "Instant Map/InstantMapRes.h"


CInstantMapRes::CInstantMapRes(const int in_mapType) : CMapRes(in_mapType) // line 13
{
	m_bOK = true;
}


CInstantMapRes::~CInstantMapRes(void) // line 21
{
}


hook_method<mystd::string (CInstantMapRes::*)(void)> CInstantMapRes::_GetLoadFileName(SERVER, "CInstantMapRes::GetLoadFileName");
mystd::string CInstantMapRes::GetLoadFileName(void) // line 28
{
	return (this->*_GetLoadFileName)();

	//TODO
}


hook_method<const bool (CInstantMapRes::*)(void) const> CInstantMapRes::_isInstantMap(SERVER, "CInstantMapRes::isInstantMap");
const bool CInstantMapRes::isInstantMap(void) const // line ??
{
	return (this->*_isInstantMap)();

	return true;
}
