#include "CCashItemShopDB.hpp"


hook_ptr<CCashItemShopDB*> CCashItemShopDB::m_cpSelf(SERVER, "CCashItemShopDB::m_cpSelf"); // = ?


CCashItemShopDB::CCashItemShopDB(void) // line 18
{
}


CCashItemShopDB::~CCashItemShopDB(void) // line 24
{
}


hook_method<static CCashItemShopDB* (__cdecl *)(void)> CCashItemShopDB::_GetObj(SERVER, "CCashItemShopDB::GetObj");
class CCashItemShopDB* CCashItemShopDB::GetObj(void) // line 191
{
	return (CCashItemShopDB::_GetObj)();

	//TODO
}


hook_method<bool (CCashItemShopDB::*)(const int in_AID, const char* in_pAccountName, int& out_Error_code, int& out_Cash)> CCashItemShopDB::_GetCash(SERVER, "CCashItemShopDB::GetCash");
bool CCashItemShopDB::GetCash(const int in_AID, const char* in_pAccountName, int& out_Error_code, int& out_Cash)
{
	return (this->*_GetCash)(in_AID, in_pAccountName, out_Error_code, out_Cash);

	//TODO
}


/* hook_method<bool (CCashItemShopDB::*)(const int in_AID, const char* in_pAccountName, const int in_plusValue, const int in_item_id, const int in_item_count, int& out_Error_code, int& out_Cash_Before, int& out_Cash_After)> CCashItemShopDB::_PlusUpdateCash(SERVER, "CCashItemShopDB::PlusUpdateCash");
bool CCashItemShopDB::PlusUpdateCash(const int in_AID, const char* in_pAccountName, const int in_plusValue, const int in_item_id, const int in_item_count, int& out_Error_code, int& out_Cash_Before, int& out_Cash_After)
{
	return (this->*_PlusUpdateCash)(in_AID, in_pAccountName, in_plusValue, in_item_id, in_item_count, out_Error_code, out_Cash_Before, out_Cash_After);

	//TODO
} */


hook_method<bool (CCashItemShopDB::*)(const int in_AID, const char* in_pAccountName, const int in_minusValue, const int in_item_id, const int in_item_count, int& out_Error_code, int& out_Cash_Before, int& out_Cash_After)> CCashItemShopDB::_MinusUpdateCash(SERVER, "CCashItemShopDB::MinusUpdateCash");
bool CCashItemShopDB::MinusUpdateCash(const int in_AID, const char* in_pAccountName, const int in_minusValue, const int in_item_id, const int in_item_count, int& out_Error_code, int& out_Cash_Before, int& out_Cash_After)
{
	return (this->*_MinusUpdateCash)(in_AID, in_pAccountName, in_minusValue, in_item_id, in_item_count, out_Error_code, out_Cash_Before, out_Cash_After);

	//TODO
}

