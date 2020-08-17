#include "AsyncDBWork/DeleteCoupleADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"


CDeleteCoupleADBWork::CDeleteCoupleADBWork(const unsigned long in_AID, const unsigned long in_GID)
: NAsyncDBWork(TYPE_DELETE_COUPLE),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_GID(in_GID)
{
	this->NAsyncDBWork::Init(in_AID);
}


CDeleteCoupleADBWork::~CDeleteCoupleADBWork()
{
}


const CDeleteCoupleADBWork::enumResult CDeleteCoupleADBWork::GetResult()
{
	return m_Result;
}


const unsigned long CDeleteCoupleADBWork::GetGID()
{
	return m_GID;
}


bool CDeleteCoupleADBWork::ExecQuery(NODBCCtrl& in_CharacterODBCCtrl)
{
	NODBCHandler Handler(in_CharacterODBCCtrl);

	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<unsigned long*>(&m_GID), 0, 0);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call Usp_DeleteCouple(?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return false;
	}

	m_Result = RESULT_SUCCESS;
	return true;
}
