#include "ItemPackageScript.h"


CItemPackageScript*& CItemPackageScript::m_cpSelf = *(CItemPackageScript**)DetourFindFunction(SERVER, "CItemPackageScript::m_cpSelf");


CItemPackageScript::CItemPackageScript(void) // line 15
{
	m_bOK = true;
}


CItemPackageScript::~CItemPackageScript(void) // line 22
{
}


hook_method<static CItemPackageScript* (__cdecl *)(void)> CItemPackageScript::_GetObj(SERVER, "CItemPackageScript::GetObj");
CItemPackageScript* CItemPackageScript::GetObj(void) // line 33
{
	return (CItemPackageScript::_GetObj)();

	//TODO
}


hook_method<bool (CItemPackageScript::*)(void)> CItemPackageScript::_Init(SERVER, "CItemPackageScript::Init");
bool CItemPackageScript::Init(void) // line 117
{
	return (this->*_Init)();

	//TODO
}
