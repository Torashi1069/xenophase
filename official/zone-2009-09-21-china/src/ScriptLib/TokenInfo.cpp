#include "ScriptLib/TokenInfo.h"


hook_method<void (CTokenMap::*)(const char* name, int type, int num, char* str)> CTokenMap::_Set(SERVER, "?Set@CTokenMap@@QAEXPBDHHPAD@Z");
void CTokenMap::Set(const char* name, int type, int num, char* str) // line 17
{
	return (this->*_Set)(name, type, num, str);

	//TODO
}
