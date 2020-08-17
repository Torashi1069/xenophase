#include "CCashItemShopScript.hpp"


CCashItemShopScript::CCashItemShopScript(void)
{
}


CCashItemShopScript::~CCashItemShopScript(void)
{
}


hook_method<static CCashItemShopScript* (__cdecl *)(void)> CCashItemShopScript::_GetObj(SERVER, "CCashItemShopScript::GetObj");
CCashItemShopScript* CCashItemShopScript::GetObj(void)
{
	return (CCashItemShopScript::_GetObj)();

	//TODO
}


hook_method<mystd::vector<CCashItemShopScript::CProduct>* (CCashItemShopScript::*)(const mystd::string in_strStandName)> CCashItemShopScript::_GetStandMapPtr(SERVER, "CCashItemShopScript::GetStandMapPtr");
mystd::vector<CCashItemShopScript::CProduct>* CCashItemShopScript::GetStandMapPtr(const mystd::string in_strStandName)
{
	return (this->*_GetStandMapPtr)(in_strStandName);

	mystd::map< mystd::string, mystd::vector<CCashItemShopScript::CProduct> >::iterator it = m_ItemStandContainer.find(in_strStandName);
	return ( it != m_ItemStandContainer.end() ) ? &it->second : NULL;
}


hook_method<bool (CCashItemShopScript::*)(void)> CCashItemShopScript::_Init(SERVER, "CCashItemShopScript::Init");
bool CCashItemShopScript::Init(void)
{
	return (this->*_Init)();

	//TODO
}
