#include "CPCItem.hpp"


CPCItem::CPCItem(void) // line 20
{
}


CPCItem::~CPCItem(void) // line 24
{
}


hook_method<int (CPCItem::*)(const char* buf, short len)> CPCItem::_ParseItem(SERVER, "CPCItem::ParseItem");
int CPCItem::ParseItem(const char* buf, short len)
{
	return (this->*_ParseItem)(buf, len);

	//TODO
}


hook_method<int (CPCItem::*)(const char* buf, short len)> CPCItem::_ParseStoredItem(SERVER, "CPCItem::ParseStoredItem");
int CPCItem::ParseStoredItem(const char* buf, short len)
{
	return (this->*_ParseStoredItem)(buf, len);

	//TODO
}


hook_method<int (CPCItem::*)(const char* buf, short len)> CPCItem::_ParseCartItem(SERVER, "CPCItem::ParseCartItem");
int CPCItem::ParseCartItem(const char* buf, short len)
{
	return (this->*_ParseCartItem)(buf, len);

	//TODO
}


hook_method<void (CPCItem::*)(void)> CPCItem::_CheckStateSpecialItem(SERVER, "CPCItem::CheckStateSpecialItem");
void CPCItem::CheckStateSpecialItem(void) // line 227-248
{
	return (this->*_CheckStateSpecialItem)();

	//TODO
}


hook_method<void (CPCItem::*)(unsigned long itmID)> CPCItem::_OnEquipedSpecialITM(SERVER, "CPCItem::OnEquipedSpecialITM");
void CPCItem::OnEquipedSpecialITM(unsigned long itmID) // line 328
{
	return (this->*_OnEquipedSpecialITM)(itmID);

	//TODO
}


hook_method<void (CPCItem::*)(unsigned long itmID)> CPCItem::_OnTakeOffSpecialITM(SERVER, "CPCItem::OnTakeOffSpecialITM");
void CPCItem::OnTakeOffSpecialITM(unsigned long itmID) // line 340
{
	return (this->*_OnTakeOffSpecialITM)(itmID);

	//TODO
}
