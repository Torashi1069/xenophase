#include "CPCBattleMercenary.hpp"


CPCBattleMercenary::CPCBattleMercenary(void)
{
	this->CPCBattleMercenary::Clear();
}


CPCBattleMercenary::~CPCBattleMercenary(void)
{
}


hook_method<void (CPCBattleMercenary::*)(void)> CPCBattleMercenary::_Clear(SERVER, "CPCBattleMercenary::Clear");
void CPCBattleMercenary::Clear(void)
{
	return (this->*_Clear)();

	//TODO
}


//hook_method<bool (CPCBattleMercenary::*)(void)> CPCBattleMercenary::_isCall(SERVER, "CPCBattleMercenary::isCall");
bool CPCBattleMercenary::isCall(void)
{
//	return (this->*_isCall)();

	return m_bCall;
}


hook_method<CPCBattleMercenary& (CPCBattleMercenary::*)(const CPCBattleMercenary::tagDBData& in_rhs)> CPCBattleMercenary::_operator_assign(SERVER, "??4CPCBattleMercenary@@QAEAAV0@ABUtagDBData@0@@Z");
CPCBattleMercenary& CPCBattleMercenary::operator=(const CPCBattleMercenary::tagDBData& in_rhs)
{
	return (this->*_operator_assign)(in_rhs);

	//TODO
}


hook_method<CPCBattleMercenary::tagDBData (CPCBattleMercenary::*)(void)> CPCBattleMercenary::_operator_tagDBData(SERVER, "??BCPCBattleMercenary@@QAE?AUtagDBData@0@XZ");
CPCBattleMercenary::operator CPCBattleMercenary::tagDBData(void)
{
	return (this->*_operator_tagDBData)();

	//TODO
}
