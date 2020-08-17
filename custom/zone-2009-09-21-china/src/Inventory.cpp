#include "Inventory.h"


CInventory::CInventory(void) // line 5
{
}


CInventory::~CInventory(void) // line 9
{
}


hook_method<void (CInventory::*)(Request* request)> CInventory::_Delete(SERVER, "CInventory::Delete");
void CInventory::Delete(Request* request) // line 21 (Inventory.h)
{
	return (this->*_Delete)(request);

	;
}


hook_method<void (CInventory::*)(Request* request)> CInventory::_Load(SERVER, "CInventory::Load");
void CInventory::Load(Request* request) // line ???
{
	return (this->*_Load)(request);

	;
}


hook_method<void (CInventory::*)(Request* request)> CInventory::_Save(SERVER, "CInventory::Save");
void CInventory::Save(Request* request) // line ???
{
	return (this->*_Save)(request);

	;
}


hook_method<int  (CInventory::*)(Request* request)> CInventory::_OnRequest(SERVER, "CInventory::OnRequest");
int CInventory::OnRequest(Request* request) // line ???
{
	return (this->*_OnRequest)(request);

	return 0;
}
