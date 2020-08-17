#include "CJobCodeForItem.hpp"


hook_method<bool (CJobCodeForItem::*)(void)> CJobCodeForItem::_Init(SERVER, "CJobCodeForItem::Init");
bool CJobCodeForItem::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(short job, unsigned long jobCode)> CJobCodeForItem::_IsJobForEquip(SERVER, "CJobCodeForItem::IsJobForEquip");
bool CJobCodeForItem::IsJobForEquip(short job, unsigned long jobCode)
{
	return (this->*_IsJobForEquip)(job, jobCode);

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(short job)> CJobCodeForItem::_IsJobForArrow(SERVER, "CJobCodeForItem::IsJobForArrow");
bool CJobCodeForItem::IsJobForArrow(short job)
{
	return (this->*_IsJobForArrow)(job);

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(int func, mystd::deque<TokenData>& parm, TokenData& ret)> CJobCodeForItem::_OnFunc(SERVER, "CJobCodeForItem::OnFunc");
bool CJobCodeForItem::OnFunc(int func, mystd::deque<TokenData>& parm, TokenData& ret)
{
	return (this->*_OnFunc)(func, parm, ret);

	//TODO
}


hook_method<void (CJobCodeForItem::*)(const char* str)> CJobCodeForItem::_OnError(SERVER, "CJobCodeForItem::OnError");
void CJobCodeForItem::OnError(const char* str)
{
	return (this->*_OnError)(str);

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(void)> CJobCodeForItem::_Compile(SERVER, "CJobCodeForItem::Compile");
bool CJobCodeForItem::Compile(void)
{
	return (this->*_Compile)();

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSet(SERVER, "CJobCodeForItem::FuncSet");
bool CJobCodeForItem::FuncSet(mystd::deque<TokenData>& parm)
{
	return (this->*_FuncSet)(parm);

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSetJC_EXN(SERVER, "CJobCodeForItem::FuncSetJC_EXN");
bool CJobCodeForItem::FuncSetJC_EXN(mystd::deque<TokenData>& parm)
{
	return (this->*_FuncSetJC_EXN)(parm);

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSetJC_ALL(SERVER, "CJobCodeForItem::FuncSetJC_ALL");
bool CJobCodeForItem::FuncSetJC_ALL(mystd::deque<TokenData>& parm)
{
	return (this->*_FuncSetJC_ALL)(parm);

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSetGroup(SERVER, "CJobCodeForItem::FuncSetGroup");
bool CJobCodeForItem::FuncSetGroup(mystd::deque<TokenData>& parm)
{
	return (this->*_FuncSetGroup)(parm);

	//TODO
}


hook_method<bool (CJobCodeForItem::*)(mystd::deque<TokenData>& parm)> CJobCodeForItem::_FuncSet2(SERVER, "CJobCodeForItem::FuncSet2");
bool CJobCodeForItem::FuncSet2(mystd::deque<TokenData>& parm)
{
	return (this->*_FuncSet2)(parm);

	//TODO
}
