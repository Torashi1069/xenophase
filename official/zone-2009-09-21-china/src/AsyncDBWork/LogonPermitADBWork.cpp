#include "AsyncDBWork/LogonPermitADBWork.h"


CLogonPermitADBWork::CLogonPermitADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_SelectedCharNum, const char* in_pIDstr, const unsigned long in_TotalUsingTime)
: NAsyncDBWork(TYPE_LOGON_PERMIT, in_AID), m_AID(in_AID), m_GID(in_GID), m_SelectedCharNum(in_SelectedCharNum), m_TotalUsingTime(in_TotalUsingTime)
{
	m_Result = RESULT_ERROR_UNKNOWN;
	memcpy(m_IDstr, in_pIDstr, sizeof(m_IDstr));
}


CLogonPermitADBWork::~CLogonPermitADBWork(void)
{
}


hook_method<bool (CLogonPermitADBWork::*)(NODBCCtrl& in_ODBCCtrl)> CLogonPermitADBWork::_ExecQuery(SERVER, "CLogonPermitADBWork::ExecQuery");
bool CLogonPermitADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	return (this->*_ExecQuery)(in_ODBCCtrl);

	//TODO
}
