#include "Base/Util.h"


hook_func<void (__cdecl *)(mystd::string& s)> _MakeStringLower("MakeStringLower");
void __cdecl MakeStringLower(mystd::string& s)
{
	return (_MakeStringLower)(s);

	//TODO
}


hook_func<CScheduler (CScheduler::*)(void)> CScheduler::_cCScheduler("CScheduler::CScheduler");
CScheduler::CScheduler(void)
{
	(this->*_cCScheduler)(); return;
}


hook_func<void (CScheduler::*)(void)> CScheduler::_dCScheduler("CScheduler::~CScheduler");
CScheduler::~CScheduler(void)
{
	(this->*_dCScheduler)(); return;
}


hook_func<void (CScheduler::*)(void)> CScheduler::_Clear("CScheduler::Clear");
void CScheduler::Clear(void)
{
	return (this->*_Clear)();
}


hook_func<void (CScheduler::*)(void)> CScheduler::_OnRun("CScheduler::OnRun");
void CScheduler::OnRun(void)
{
	return (this->*_OnRun)();
}


hook_func<bool (CScheduler::*)(long excuteTime, int excuteType, void (__cdecl* pfunc)())> CScheduler::_InsertInList("CScheduler::InsertInList(1)");
bool CScheduler::InsertInList(long excuteTime, int excuteType, void (__cdecl* pfunc)())
{
	return (this->*_InsertInList)(excuteTime, excuteType, pfunc);
}


hook_func<bool (CScheduler::*)(long excuteTime, POINTER_FUNC pfunc)> CScheduler::_InsertInList2("CScheduler::InsertInList(2)");
bool CScheduler::InsertInList(long excuteTime, POINTER_FUNC pfunc)
{
	return (this->*_InsertInList2)(excuteTime, pfunc);
}


hook_func<CScheduler* (__cdecl *)(void)> CScheduler::_getInstance("CScheduler::getInstance");
CScheduler* __cdecl CScheduler::getInstance(void)
{
	return (CScheduler::_getInstance)();
}
