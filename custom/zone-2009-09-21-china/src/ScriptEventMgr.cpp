#include "ScriptEventMgr.h"


hook_method<void (CScriptEventMgr::*)(void)> CScriptEventMgr::_Process(SERVER, "CScriptEventMgr::Process");
void CScriptEventMgr::Process(void)
{
	return (this->*_Process)();

	//TODO
}
