#include "CDungeonScript.hpp"


CDungeonScript::CDungeonScript(void)
{
}


CDungeonScript::~CDungeonScript(void)
{
}


hook_method<bool (CDungeonScript::*)(const char* instantName)> CDungeonScript::_Insert(SERVER, "CDungeonScript::Insert");
bool CDungeonScript::Insert(const char* instantName)
{
	return (this->*_Insert)(instantName);

	//TODO
}


hook_method<bool (CDungeonScript::*)(const char* mapName, const char* FileName)> CDungeonScript::_AddScript(SERVER, "CDungeonScript::AddScript");
bool CDungeonScript::AddScript(const char* mapName, const char* FileName)
{
	return (this->*_AddScript)(mapName, FileName);

	//TODO
}


hook_method<const char* (CDungeonScript::*)(void)> CDungeonScript::_GetDungeonName(SERVER, "CDungeonScript::GetDungeonName");
const char* CDungeonScript::GetDungeonName(void)
{
	return (this->*_GetDungeonName)();

	//TODO
}


hook_method<bool (CDungeonScript::*)(const char* name, mystd::list<mystd::string>& scriptList)> CDungeonScript::_GetList(SERVER, "CDungeonScript::GetList");
bool CDungeonScript::GetList(const char* name, mystd::list<mystd::string>& scriptList)
{
	return (this->*_GetList)(name, scriptList);

	//TODO
}


hook_method<void (CDungeonScript::*)(void)> CDungeonScript::_GetNext(SERVER, "CDungeonScript::GetNext");
void CDungeonScript::GetNext(void)
{
	return (this->*_GetNext)();

	//TODO
}


//hook_method<int (CDungeonScript::*)(void)> CDungeonScript::_GetCount(SERVER, "CDungeonScript::GetCount");
int CDungeonScript::GetCount(void)
{
//	return (this->*_GetCount)();

	return m_map.size();
}
