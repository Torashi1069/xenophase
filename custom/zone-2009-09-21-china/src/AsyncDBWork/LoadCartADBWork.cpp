#include "AsyncDBWork/LoadCartADBWork.h"


CLoadCartADBWork::CLoadCartADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_SKLevel) // line 18
: NAsyncDBWork(TYPE_LOAD_CART, in_AID), m_AID(in_AID), m_GID(in_GID), m_Result(RESULT_ERROR_UNKNOWN), m_Length(0), m_SKLevel(in_SKLevel)
{
}


CLoadCartADBWork::~CLoadCartADBWork(void) // line 23
{
}


hook_method<bool (CLoadCartADBWork::*)(NODBCCtrl& in_ODBCCtrl)> CLoadCartADBWork::_ExecQuery(SERVER, "CLoadCartADBWork::ExecQuery");
bool CLoadCartADBWork::ExecQuery(class NODBCCtrl& in_ODBCCtrl) // line 30
{
	return (this->*_ExecQuery)(in_ODBCCtrl);

	//TODO
}
