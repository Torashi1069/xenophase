#include "AsyncDBWork/ElementalDeleteADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"


CElementalDeleteADBWork::CElementalDeleteADBWork(const unsigned long in_AID, const unsigned long in_GID)
: NAsyncDBWork(TYPE_ELEMENTAL_DELETE),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_GID(in_GID)
{
	this->NAsyncDBWork::Init(in_AID);
}


CElementalDeleteADBWork::~CElementalDeleteADBWork()
{
}


unsigned long CElementalDeleteADBWork::GetGID()
{
	return m_GID;
}


CElementalDeleteADBWork::enumResult CElementalDeleteADBWork::GetResult()
{
	return m_Result;
}


bool CElementalDeleteADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_SUCCESS;

	NAsyncDBWork::enumRETURN ret = this->CElementalDeleteADBWork::Delete(in_ODBCCtrl);
	if( ret != NAsyncDBWork::RETURN_SUCCESS )
	{
		m_Result = RESULT_ERROR_ELEMENTAL_DELETE;
		if( ret == NAsyncDBWork::RETURN_ERROR_ODBC )
			return false;
	}

	return true;
}


NAsyncDBWork::enumRETURN CElementalDeleteADBWork::Delete(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<unsigned long*>(&m_GID), sizeof(m_GID), &cbInt);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_elemental_delete(?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
