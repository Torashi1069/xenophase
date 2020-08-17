#include "AsyncDBWork/MercenaryDeleteADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"
#include "shared/NCriticalErrorLog.h"


CMercenaryDeleteADBWork::CMercenaryDeleteADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_reason)
: NAsyncDBWork(TYPE_MERCENARY_DELETE),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_GID(in_GID),
  m_AID(in_AID),
  m_reason(in_reason)
{
	this->NAsyncDBWork::Init(in_AID);
}


CMercenaryDeleteADBWork::~CMercenaryDeleteADBWork()
{
}


const unsigned long CMercenaryDeleteADBWork::GetAID()
{
	return m_AID;
}


const unsigned long CMercenaryDeleteADBWork::GetGID()
{
	return m_GID;
}


const CMercenaryDeleteADBWork::enumResult CMercenaryDeleteADBWork::GetResult()
{
	return m_Result;
}


const int CMercenaryDeleteADBWork::GetReason()
{
	return m_reason;
}


bool CMercenaryDeleteADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_SUCCESS;

	NAsyncDBWork::enumRETURN ret = this->CMercenaryDeleteADBWork::Delete(in_ODBCCtrl);
	if( ret != NAsyncDBWork::RETURN_SUCCESS )
	{
		m_Result = RESULT_ERROR_MERCENARY_DELETE;
		if( ret == NAsyncDBWork::RETURN_ERROR_ODBC )
			return false;
	}

	return true;
}


NAsyncDBWork::enumRETURN CMercenaryDeleteADBWork::Delete(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<unsigned long*>(&m_GID), sizeof(m_GID), &cbInt);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_mercenary_delete(?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	int ret_code = 0;
	Handler.NODBCHandler::BindCol(1, SQL_C_SLONG, &ret_code, sizeof(ret_code), &cbInt);

	SQLRETURN sqlRet2 = Handler.NODBCHandler::Fetch();
	if( !SQL_SUCCEEDED(sqlRet2) )
		return NAsyncDBWork::RETURN_ERROR;

	if( ret_code <= 0 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "용병삭제에러 charID=%d", m_GID);
		return NAsyncDBWork::RETURN_ERROR;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
