#include "CItemList.hpp"


hook_method<void (CItemList::*)(const char* fileName, int verDate)> CItemList::_LoadFromFile(SERVER, "CItemList::LoadFromFile");
void CItemList::LoadFromFile(const char* fileName, int verDate)
{
	return (this->*_LoadFromFile)(fileName, verDate);

	//TODO
}


hook_method<int (CItemList::*)(int n)> CItemList::_GetNth(SERVER, "CItemList::GetNth");
int CItemList::GetNth(int n)
{
	return (this->*_GetNth)(n);

	//TODO
}
