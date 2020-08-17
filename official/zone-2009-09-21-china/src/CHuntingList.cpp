#include "CHuntingList.hpp"


CHuntingList::CHuntingList(void)
{
}


CHuntingList::~CHuntingList(void)
{
}


hook_method<bool (CHuntingList::*)(void)> CHuntingList::_IsHuntingListFull(SERVER, "CHuntingList::IsHuntingListFull");
bool CHuntingList::IsHuntingListFull(void)
{
	return (this->*_IsHuntingListFull)();

	//TODO
}


hook_method<int (CHuntingList::*)(int mob)> CHuntingList::_FindHuntingList(SERVER, "CHuntingList::FindHuntingList");
int CHuntingList::FindHuntingList(int mob)
{
	return (this->*_FindHuntingList)(mob);

	//TODO
}


hook_method<int (CHuntingList::*)(int mob)> CHuntingList::_AddHuntingList(SERVER, "CHuntingList::AddHuntingList");
int CHuntingList::AddHuntingList(int mob)
{
	return (this->*_AddHuntingList)(mob);

	//TODO
}


hook_method<bool (CHuntingList::*)(int mob)> CHuntingList::_DeleteHuntingList(SERVER, "CHuntingList::DeleteHuntingList");
bool CHuntingList::DeleteHuntingList(int mob)
{
	return (this->*_DeleteHuntingList)(mob);

	//TODO
}


hook_method<bool (CHuntingList::*)(int mob, int count)> CHuntingList::_SetHuntingList(SERVER, "CHuntingList::SetHuntingList");
bool CHuntingList::SetHuntingList(int mob, int count)
{
	return (this->*_SetHuntingList)(mob, count);

	//TODO
}


hook_method<void (CHuntingList::*)(void)> CHuntingList::_ClearHuntingList(SERVER, "CHuntingList::ClearHuntingList");
void CHuntingList::ClearHuntingList(void)
{
	return (this->*_ClearHuntingList)();

	//TODO
}


hook_method<int (CHuntingList::*)(unsigned char* buf, int len)> CHuntingList::_ReadBinary(SERVER, "CHuntingList::ReadBinary");
int CHuntingList::ReadBinary(unsigned char* buf, int len)
{
	return (this->*_ReadBinary)(buf, len);

	//TODO
}


hook_method<int (CHuntingList::*)(unsigned char* buf, int& len)> CHuntingList::_WriteBinary(SERVER, "CHuntingList::WriteBinary");
int CHuntingList::WriteBinary(unsigned char* buf, int& len)
{
	return (this->*_WriteBinary)(buf, len);

	//TODO
}


hook_method<bool (CHuntingList::*)(int mob)> CHuntingList::_PlusOneCount(SERVER, "CHuntingList::PlusOneCount");
bool CHuntingList::PlusOneCount(int mob)
{
	return (this->*_PlusOneCount)(mob);

	//TODO
}


hook_method<void (CHuntingList::*)(mystd::string& str)> CHuntingList::_DisplayHuntingList(SERVER, "CHuntingList::DisplayHuntingList");
void CHuntingList::DisplayHuntingList(mystd::string& str)
{
	return (this->*_DisplayHuntingList)(str);

	//TODO
}


hook_method<void (CHuntingList::*)(mystd::string& str)> CHuntingList::_DisplayHuntingList2(SERVER, "CHuntingList::DisplayHuntingList2");
void CHuntingList::DisplayHuntingList2(mystd::string& str)
{
	return (this->*_DisplayHuntingList2)(str);

	//TODO
}


hook_method<int (CHuntingList::*)(void)> CHuntingList::_UseHuntingList(SERVER, "CHuntingList::UseHuntingList");
int CHuntingList::UseHuntingList(void)
{
	return (this->*_UseHuntingList)();

	//TODO
}


hook_method<int (CHuntingList::*)(int mob)> CHuntingList::_CheckHuntingList(SERVER, "CHuntingList::CheckHuntingList");
int CHuntingList::CheckHuntingList(int mob)
{
	return (this->*_CheckHuntingList)(mob);

	//TODO
}
