#include "Memorial Dungeon/MemorialDungeonConfiguration.h"


hook_val<const mystd::string> CMemorialDungeonConfiguration::m_szConfigFileName(SERVER, "CMemorialDungeonConfiguration::m_szConfigFileName"); // = { 0 };
hook_ptr<CMemorialDungeonConfiguration*> CMemorialDungeonConfiguration::m_cpSelf(SERVER, "CMemorialDungeonConfiguration::m_cpSelf"); // = NULL;


hook_func<CMemorialDungeonConfiguration* (__cdecl *)(void)> _InstanceCMemorialDungeonConfiguration(SERVER, "InstanceCMemorialDungeonConfiguration");
CMemorialDungeonConfiguration* __cdecl InstanceCMemorialDungeonConfiguration(void) // line 92
{
	return (_InstanceCMemorialDungeonConfiguration)();

	return CMemorialDungeonConfiguration::m_cpSelf;
}


CMemorialDungeonConfiguration::CMemorialDungeonConfiguration(void) // line 23-29
{
	m_EnterLimitMinute = 5;
	m_bDataBaseLogOutput = false;
	m_SubscriptionMinimumDelaySecond = 60;
	m_bOpen = true;
	m_bOK = false;

	if( this->CMemorialDungeonConfiguration::Create() )
		m_bOK = true;
}


CMemorialDungeonConfiguration::~CMemorialDungeonConfiguration(void) // line 32-34
{
}


hook_method<bool (CMemorialDungeonConfiguration::*)(void)> CMemorialDungeonConfiguration::_Create(SERVER, "CMemorialDungeonConfiguration::Create");
bool CMemorialDungeonConfiguration::Create(void) // line 38-78
{
	return (this->*_Create)();

	//TODO
}


hook_method<void (CMemorialDungeonConfiguration::*)(void)> CMemorialDungeonConfiguration::_Destroy(SERVER, "CMemorialDungeonConfiguration::Destroy");
void CMemorialDungeonConfiguration::Destroy(void) // line 238-241
{
	return (this->*_Destroy)();

	//TODO
}


hook_method<bool (CMemorialDungeonConfiguration::*)(void) const> CMemorialDungeonConfiguration::_IsDBLogOutput(SERVER, "CMemorialDungeonConfiguration::IsDBLogOutput");
bool CMemorialDungeonConfiguration::IsDBLogOutput(void) const // line 66 (Memorial Dungeon/MemorialDungeonConfiguration.h)
{
	return (this->*_IsDBLogOutput)();

	return m_bDataBaseLogOutput;
}


hook_method<bool (CMemorialDungeonConfiguration::*)(void)> CMemorialDungeonConfiguration::_IsOpen(SERVER, "CMemorialDungeonConfiguration::IsOpen");
bool CMemorialDungeonConfiguration::IsOpen(void) // line 81-86
{
	return (this->*_IsOpen)();

	//TODO
}
