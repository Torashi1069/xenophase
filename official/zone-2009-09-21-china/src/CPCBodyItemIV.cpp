#include "CPCBodyItemIV.hpp"


hook_method<IVItItem* (CPCBodyItemIV::*)(IVItItem* item, int par1, int isIndexChangable)> CPCBodyItemIV::_Add(SERVER, "CPCBodyItemIV::Add");
hook_method<void (CPCBodyItemIV::*)(void)> CPCBodyItemIV::_Init(SERVER, "CPCBodyItemIV::Init");
hook_method<void (CPCBodyItemIV::*)(void)> CPCBodyItemIV::_Reset(SERVER, "CPCBodyItemIV::Reset");
hook_method<int (CPCBodyItemIV::*)(short index, short count)> CPCBodyItemIV::_Delete2(SERVER, "?Delete@CPCBodyItemIV@@UAEHFF@Z");
hook_method<int (CPCBodyItemIV::*)(short index)> CPCBodyItemIV::_Delete3(SERVER, "?Delete@CPCBodyItemIV@@UAEHF@Z");
hook_method<int (CPCBodyItemIV::*)(void)> CPCBodyItemIV::_GetSize(SERVER, "CPCBodyItemIV::GetSize");


CPCBodyItemIV::CPCBodyItemIV(void)
{
}


CPCBodyItemIV::~CPCBodyItemIV(void)
{
}


IVItItem* CPCBodyItemIV::Add(IVItItem* item, int par1, int isIndexChangable)
{
	return (this->*_Add)(item, par1, isIndexChangable);

	//TODO
}


void CPCBodyItemIV::Init(void)
{
	return (this->*_Init)();

	//TODO
}


void CPCBodyItemIV::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


int CPCBodyItemIV::Delete(short index, short count)
{
	return (this->*_Delete2)(index, count);

	//TODO
}


int CPCBodyItemIV::Delete(short index)
{
	return (this->*_Delete3)(index);

	//TODO
}


int CPCBodyItemIV::GetSize(void)
{
	return (this->*_GetSize)();

	//TODO
}
