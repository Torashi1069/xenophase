#include "PCStoreItemIV.h"


CPCStoreItemIV::CPCStoreItemIV() // line 9-10
{
}


CPCStoreItemIV::~CPCStoreItemIV() // line 13-14
{
}


hook_func<void (CPCStoreItemIV::*)()> CPCStoreItemIV::_Init(SERVER, "CPCStoreItemIV::Init");
void CPCStoreItemIV::Init()
{
	return (this->*_Init)();

	//TODO
}


hook_func<int (CPCStoreItemIV::*)(short index, short count)> CPCStoreItemIV::_Delete(SERVER, "CPCStoreItemIV::Delete");
int CPCStoreItemIV::Delete(short index, short count)
{
	return (this->*_Delete)(index, count);

	//TODO
}


hook_func<IVItItem* (CPCStoreItemIV::*)(short index, short count)> CPCStoreItemIV::_Remove(SERVER, "CPCStoreItemIV::Remove");
IVItItem* CPCStoreItemIV::Remove(short index, short count) // line 42-57
{
	return (this->*_Remove)(index, count);

	//TODO
}


hook_func<BOOL (CPCStoreItemIV::*)()> CPCStoreItemIV::_IsOpen(SERVER, "CPCStoreItemIV::IsOpen");
BOOL CPCStoreItemIV::IsOpen()
{
	return (this->*_IsOpen)();

	return m_isStoreOpen;
}


hook_func<void (CPCStoreItemIV::*)()> CPCStoreItemIV::_Reset(SERVER, "CPCStoreItemIV::Reset");
void CPCStoreItemIV::Reset()
{
	return (this->*_Reset)();

	//TODO
}


//hook_func<void (CPCStoreItemIV::*)(BOOL isStoreOpen)> CPCStoreItemIV::_SetStoreOpenFlag(SERVER, "CPCStoreItemIV::SetStoreOpenFlag");
void CPCStoreItemIV::SetStoreOpenFlag(BOOL isStoreOpen)
{
//	return (this->*_SetStoreOpenFlag)(isStoreOpen);

	m_isStoreOpen = isStoreOpen;
}
