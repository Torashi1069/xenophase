#include "MapInfo.h"


hook_method<void (CMapInfo::*)(void)> CMapInfo::_GetMapInfo(SERVER, "CMapInfo::GetMapInfo");
void CMapInfo::GetMapInfo(void)
{
	return (this->*_GetMapInfo)();

	//TODO
}
