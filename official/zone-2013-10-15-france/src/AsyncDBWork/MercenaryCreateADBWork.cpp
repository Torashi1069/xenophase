#include "AsyncDBWork/MercenaryCreateADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"
#include "shared/NCriticalErrorLog.h"


CMercenaryCreateADBWork::CMercenaryCreateADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_Job, const int in_RemainLifeSECOND)
: NAsyncDBWork(TYPE_MERCENARY_CREATE),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_GID(in_GID),
  m_AID(in_AID),
  m_Job(in_Job),
  m_RemainLifeSECOND(in_RemainLifeSECOND)
{
	this->NAsyncDBWork::Init(in_AID);
}


CMercenaryCreateADBWork::~CMercenaryCreateADBWork()
{
}


const unsigned long CMercenaryCreateADBWork::GetAID()
{
	return m_AID;
}


const unsigned long CMercenaryCreateADBWork::GetGID()
{
	return m_GID;
}


const int CMercenaryCreateADBWork::GetJob()
{
	return m_Job;
}


const CMercenaryCreateADBWork::enumResult CMercenaryCreateADBWork::GetResult()
{
	return m_Result;
}


bool CMercenaryCreateADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_SUCCESS;

	NAsyncDBWork::enumRETURN ret = this->CMercenaryCreateADBWork::Create(in_ODBCCtrl);
	if( ret != NAsyncDBWork::RETURN_SUCCESS )
	{
		m_Result = RESULT_ERROR_MERCENARY_CREATE;
		if( ret == NAsyncDBWork::RETURN_ERROR_ODBC )
			return false;
	}

	return true;
}


NAsyncDBWork::enumRETURN CMercenaryCreateADBWork::Create(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<unsigned long*>(&m_GID), sizeof(m_GID), &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_RemainLifeSECOND), sizeof(m_RemainLifeSECOND), &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_Job), sizeof(m_Job), &cbInt);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_mercenary_createV2(?, ?, ?)}");
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

	if( ret_code == 0 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "용병생성에러 charID=%d", m_GID);
		return NAsyncDBWork::RETURN_ERROR;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
