#include "CMercenaryConfiguration.hpp"


hook_ptr<CMercenaryConfiguration *> CMercenaryConfiguration::m_cpSelf(SERVER, "CMercenaryConfiguration::m_cpSelf"); // ?


CMercenaryConfiguration::CMercenaryConfiguration(void) // line 24
{
	m_ConfigurationFileName = "mercenary.lua";
	m_bOK = false;
	if( this->CMercenaryConfiguration::Create() )
		m_bOK = true;
}


CMercenaryConfiguration::~CMercenaryConfiguration(void) // line 31
{
}


hook_method<bool (CMercenaryConfiguration::*)(void)> CMercenaryConfiguration::_Create(SERVER, "CMercenaryConfiguration::Create");
bool CMercenaryConfiguration::Create(void) // line 43
{
	return (this->*_Create)();

	//TODO
}


//hook_method<bool (CMercenaryConfiguration::*)(void)> CMercenaryConfiguration::_isOK(SERVER, "CMercenaryConfiguration::isOK");
bool CMercenaryConfiguration::isOK(void)
{
//	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (CMercenaryConfiguration::*)(int in_ITID)> CMercenaryConfiguration::_isScroll(SERVER, "CMercenaryConfiguration::isScroll");
bool CMercenaryConfiguration::isScroll(int in_ITID)
{
	return (this->*_isScroll)(in_ITID);

	//TODO
}


hook_method<static bool (__cdecl *)(void)> CMercenaryConfiguration::_CreateInstance(SERVER, "CMercenaryConfiguration::CreateInstance");
bool __cdecl CMercenaryConfiguration::CreateInstance(void) // line 81
{
	return (CMercenaryConfiguration::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CMercenaryConfiguration::_DestroyInstance(SERVER, "CMercenaryConfiguration::DestroyInstance");
void __cdecl CMercenaryConfiguration::DestroyInstance(void) // line 93
{
	return (CMercenaryConfiguration::_DestroyInstance)();

	//TODO
}
