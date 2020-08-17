#include "CPCHireItemCtrl.hpp"


hook_method<bool (CPCHireItemCtrl::*)(const __int64 in_ItemUID, CPCHireItemCtrl::CRequest& in_Request)> CPCHireItemCtrl::_RequestProcess(SERVER, "CPCHireItemCtrl::RequestProcess");
bool CPCHireItemCtrl::RequestProcess(const __int64 in_ItemUID, CPCHireItemCtrl::CRequest& in_Request)
{
	return (this->*_RequestProcess)(in_ItemUID, in_Request);

	//TODO
}


hook_method<unsigned long (CPCHireItemCtrl::*)(const long in_CurDate, const unsigned long in_CurTime, const IVItItem* const in_pItem)> CPCHireItemCtrl::_GetNexCheckTime(SERVER, "CPCHireItemCtrl::GetNexCheckTime");
unsigned long CPCHireItemCtrl::GetNexCheckTime(const long in_CurDate, const unsigned long in_CurTime, const IVItItem* const in_pItem)
{
	return (this->*_GetNexCheckTime)(in_CurDate, in_CurTime, in_pItem);

	//TODO
}


hook_method<void (CPCHireItemCtrl::*)(CPC* in_cpOwnerPC)> CPCHireItemCtrl::_Init(SERVER, "CPCHireItemCtrl::Init");
void CPCHireItemCtrl::Init(CPC* in_cpOwnerPC)
{
	return (this->*_Init)(in_cpOwnerPC);

	//TODO
}


hook_method<void (CPCHireItemCtrl::*)(void)> CPCHireItemCtrl::_Reset(SERVER, "CPCHireItemCtrl::Reset");
void CPCHireItemCtrl::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<void (CPCHireItemCtrl::*)(void)> CPCHireItemCtrl::_Process(SERVER, "CPCHireItemCtrl::Process");
void CPCHireItemCtrl::Process(void)
{
	return (this->*_Process)();

	//TODO
}


hook_method<void (CPCHireItemCtrl::*)(const enum enumInventoryType in_InventoryType, IVItItem* in_pItem)> CPCHireItemCtrl::_RequestAdd(SERVER, "CPCHireItemCtrl::RequestAdd");
void CPCHireItemCtrl::RequestAdd(const enum enumInventoryType in_InventoryType, IVItItem* in_pItem)
{
	return (this->*_RequestAdd)(in_InventoryType, in_pItem);

	//TODO
}


/* hook_method<void (CPCHireItemCtrl::*)(IVItItem* const in_pItem)> CPCHireItemCtrl::_RequestRemove(SERVER, "CPCHireItemCtrl::RequestRemove");
void CPCHireItemCtrl::RequestRemove(IVItItem* const in_pItem)
{
	return (this->*_RequestRemove)(in_pItem);

	//TODO
} */
