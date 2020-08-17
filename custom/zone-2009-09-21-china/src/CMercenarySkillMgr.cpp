#include "CMercenarySkillMgr.hpp"


hook_ptr<CMercenarySkillMgr *> CMercenarySkillMgr::m_cpSelf(SERVER, "CMercenarySkillMgr::m_cpSelf");


CMercenarySkillMgr::CMercenarySkillMgr(void) // line 28
{
	m_bOK = false;
	if( this->CMercenarySkillMgr::Create() )
		m_bOK = true;
}


CMercenarySkillMgr::~CMercenarySkillMgr(void) // line 36
{
}


hook_method<bool (CMercenarySkillMgr::*)(void)> CMercenarySkillMgr::_Create(SERVER, "CMercenarySkillMgr::Create");
bool CMercenarySkillMgr::Create(void) // line 68
{
	return (this->*_Create)();

	//TODO
}


//hook_method<void (CMercenarySkillMgr::*)(void)> CMercenarySkillMgr::_Destroy(SERVER, "CMercenarySkillMgr::Destory");
void CMercenarySkillMgr::Destroy(void) // line ??
{
//	return (this->*_Destroy)();

	;
}


hook_method<static bool (__cdecl *)(void)> CMercenarySkillMgr::_CreateInstance(SERVER, "CMercenarySkillMgr::CreateInstance");
bool __cdecl CMercenarySkillMgr::CreateInstance(void) // line 57
{
	return (CMercenarySkillMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CMercenarySkillMgr::_DestroyInstance(SERVER, "CMercenarySkillMgr::DestoryInstance");
void __cdecl CMercenarySkillMgr::DestroyInstance(void) // line 51
{
	return (CMercenarySkillMgr::_DestroyInstance)();

	//TODO
}

