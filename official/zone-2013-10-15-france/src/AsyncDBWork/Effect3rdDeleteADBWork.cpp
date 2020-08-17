#include "AsyncDBWork/Effect3rdDeleteADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"


CEffect3rdDeleteADBWork::CEffect3rdDeleteADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_EffectID)
: NAsyncDBWork(TYPE_EFFECT3RD_DELETE),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_GID(in_GID),
  m_AID(in_AID),
  m_EffectID(in_EffectID)
{
	this->NAsyncDBWork::Init(in_AID);
}


CEffect3rdDeleteADBWork::~CEffect3rdDeleteADBWork()
{
}


const unsigned long CEffect3rdDeleteADBWork::GetAID()
{
	return m_AID;
}


const unsigned long CEffect3rdDeleteADBWork::GetGID()
{
	return m_GID;
}


const CEffect3rdDeleteADBWork::enumResult CEffect3rdDeleteADBWork::GetResult()
{
	return m_Result;
}


NAsyncDBWork::enumRETURN CEffect3rdDeleteADBWork::Effect3rd_Delete(NODBCCtrl& in_ODBCCtrl, const int in_GID, const int in_ID)
{
	NODBCHandler Handler (in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&in_GID), 0, &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&in_ID), 0, &cbInt);

	SQLRETURN ret = Handler.NODBCHandler::ExecDirect("{call usp_effect_Rebuild_delete(?, ?)}");
	if( !SQL_SUCCEEDED(ret) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}


bool CEffect3rdDeleteADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_ERROR_UNKNOWN;

	NAsyncDBWork::enumRETURN ret = this->CEffect3rdDeleteADBWork::Effect3rd_Delete(in_ODBCCtrl, m_GID, m_EffectID);
	if( ret != NAsyncDBWork::RETURN_SUCCESS )
	{
		m_Result = RESULT_ERROR_UNKNOWN;
		return false;
	}

	m_Result = RESULT_SUCCESS;
	return true;
}
