#include "AsyncDBWork/SaveAllADBWork.h"


CSaveAllADBWork::CSaveAllADBWork(const enum CSaveAllADBWork::enumAfterAction in_AfterAction, const unsigned long in_AID, const unsigned long in_GID) // line 24
: NAsyncDBWork(TYPE_SAVE_ALL, in_AID), m_AID(in_AID), m_GID(in_GID), m_AfterAction(in_AfterAction), m_Result(RESULT_ERROR_UNKNOWN)
{
}


CSaveAllADBWork::~CSaveAllADBWork(void) // line 29
{
}


hook_method<bool (CSaveAllADBWork::*)(NODBCCtrl& in_ODBCCtrl)> CSaveAllADBWork::_ExecQuery(SERVER, "CSaveAllADBWork::ExecQuery");
bool CSaveAllADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	return (this->*_ExecQuery)(in_ODBCCtrl);

	//TODO
}
